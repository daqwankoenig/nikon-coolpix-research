#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef P510_ALLOW_USB
#define P510_ALLOW_USB 0
#endif

#if P510_ALLOW_USB
#include <libusb-1.0/libusb.h>
#endif

#define P510_VID 0x04B0u
#define P510_PID 0x0223u
#define P510_PTP_INTERFACE_CLASS 0x06u
#define P510_PTP_INTERFACE_SUBCLASS 0x01u
#define P510_PTP_INTERFACE_PROTOCOL 0x01u
#define PTP_OC_GET_DEVICE_INFO 0x1001u
#define PTP_TRANSACTION_ID 1u
#define PTP_SESSION_ID 0u
#define PTP_CONTAINER_COMMAND 0x0001u
#define PTP_CONTAINER_DATA 0x0002u
#define PTP_CONTAINER_RESPONSE 0x0003u
#define PTP_CONTAINER_HEADER_LEN 12u
#define PTP_RESPONSE_OK 0x2001u
#define P510_OPERATION_LIMIT 1u

typedef struct {
    uint16_t standard_version;
    uint32_t vendor_extension_id;
    uint16_t vendor_extension_version;
    char *vendor_extension_description;
    uint16_t functional_mode;
    uint16_t *operations;
    uint32_t operations_len;
    uint16_t *events;
    uint32_t events_len;
    uint16_t *device_properties;
    uint32_t device_properties_len;
    uint16_t *capture_formats;
    uint32_t capture_formats_len;
    uint16_t *image_formats;
    uint32_t image_formats_len;
    char *manufacturer;
    char *model;
    char *device_version;
    char *serial_number;
} P510DeviceInfo;

static uint16_t read_u16le(const uint8_t *p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static uint32_t read_u32le(const uint8_t *p)
{
    return (uint32_t)p[0] |
           ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static void write_u16le(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
}

static void write_u32le(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static void free_device_info(P510DeviceInfo *di)
{
    free(di->vendor_extension_description);
    free(di->operations);
    free(di->events);
    free(di->device_properties);
    free(di->capture_formats);
    free(di->image_formats);
    free(di->manufacturer);
    free(di->model);
    free(di->device_version);
    free(di->serial_number);
    memset(di, 0, sizeof(*di));
}

static int read_ptp_string(const uint8_t *data, size_t size, size_t *offset, char **out)
{
    uint8_t chars;
    size_t i;

    *out = NULL;
    if (*offset >= size)
        return 0;

    chars = data[*offset];
    (*offset)++;
    if (chars == 0) {
        *out = strdup("");
        return *out != NULL;
    }
    if (*offset + (size_t)chars * 2u > size)
        return 0;

    *out = calloc((size_t)chars * 6u + 1u, 1);
    if (*out == NULL)
        return 0;

    for (i = 0; i < chars; i++) {
        uint16_t c = read_u16le(data + *offset + i * 2u);
        if (c == 0)
            break;
        if (c >= 0x20u && c <= 0x7eu) {
            size_t n = strlen(*out);
            (*out)[n] = (char)c;
        } else if (c == 0x00E9u) {
            size_t n = strlen(*out);
            memcpy(*out + n, "\\u00E9", 6);
        } else {
            size_t n = strlen(*out);
            snprintf(*out + n, 7, "\\u%04X", c);
        }
    }
    *offset += (size_t)chars * 2u;
    return 1;
}

static int read_u16_array(const uint8_t *data, size_t size, size_t *offset,
                          uint16_t **out, uint32_t *out_len)
{
    uint32_t count;
    uint32_t i;

    *out = NULL;
    *out_len = 0;
    if (*offset + 4u > size)
        return 0;
    count = read_u32le(data + *offset);
    *offset += 4u;
    if ((size_t)count > (size - *offset) / 2u)
        return 0;

    if (count != 0) {
        *out = calloc(count, sizeof(uint16_t));
        if (*out == NULL)
            return 0;
        for (i = 0; i < count; i++) {
            (*out)[i] = read_u16le(data + *offset);
            *offset += 2u;
        }
    }
    *out_len = count;
    return 1;
}

static int parse_device_info(const uint8_t *data, size_t size, P510DeviceInfo *di)
{
    size_t offset = 0;

    memset(di, 0, sizeof(*di));
    if (size < 12u)
        return 0;

    di->standard_version = read_u16le(data + 0);
    di->vendor_extension_id = read_u32le(data + 2);
    di->vendor_extension_version = read_u16le(data + 6);
    offset = 8;

    if (!read_ptp_string(data, size, &offset, &di->vendor_extension_description))
        return 0;
    if (offset + 2u > size)
        return 0;
    di->functional_mode = read_u16le(data + offset);
    offset += 2u;

    if (!read_u16_array(data, size, &offset, &di->operations, &di->operations_len))
        return 0;
    if (!read_u16_array(data, size, &offset, &di->events, &di->events_len))
        return 0;
    if (!read_u16_array(data, size, &offset, &di->device_properties, &di->device_properties_len))
        return 0;
    if (!read_u16_array(data, size, &offset, &di->capture_formats, &di->capture_formats_len))
        return 0;
    if (!read_u16_array(data, size, &offset, &di->image_formats, &di->image_formats_len))
        return 0;

    /* libgphoto2 permits the final four strings to be malformed or absent. */
    if (!read_ptp_string(data, size, &offset, &di->manufacturer))
        di->manufacturer = strdup("UNKNOWN");
    if (!read_ptp_string(data, size, &offset, &di->model))
        di->model = strdup("UNKNOWN");
    if (!read_ptp_string(data, size, &offset, &di->device_version))
        di->device_version = strdup("UNKNOWN");
    if (!read_ptp_string(data, size, &offset, &di->serial_number))
        di->serial_number = strdup("UNKNOWN");
    return di->manufacturer && di->model && di->device_version && di->serial_number;
}

static size_t build_get_device_info_command(uint8_t out[12])
{
    memset(out, 0, 12);
    write_u32le(out + 0, PTP_CONTAINER_HEADER_LEN);
    write_u16le(out + 4, PTP_CONTAINER_COMMAND);
    write_u16le(out + 6, (uint16_t)PTP_OC_GET_DEVICE_INFO);
    write_u32le(out + 8, PTP_TRANSACTION_ID);
    return PTP_CONTAINER_HEADER_LEN;
}

static void print_command_bytes(const uint8_t *command, size_t command_len)
{
    size_t i;
    printf("OutgoingBytes=");
    for (i = 0; i < command_len; i++)
        printf("%s%02X", i == 0 ? "" : " ", command[i]);
    putchar('\n');
}

static const char *operation_name(uint16_t code)
{
    if (code == PTP_OC_GET_DEVICE_INFO)
        return "GetDeviceInfo";
    if (code >= 0x9800u && code <= 0x98FFu)
        return "MTP/VENDOR-SPECIFIC";
    if (code >= 0x9000u)
        return "VENDOR-SPECIFIC UNKNOWN";
    if (code >= 0x1000u && code <= 0x1025u)
        return "STANDARD-PTP CODE NOT TRANSMITTED";
    if (code >= 0x101Du && code <= 0x1025u)
        return "PTP 1.1 standard/vendor-extension code";
    return "UNKNOWN";
}

static void print_device_info(const P510DeviceInfo *di)
{
    uint32_t i;
    printf("StandardVersion=0x%04X\n", di->standard_version);
    printf("VendorExtensionID=0x%08X\n", di->vendor_extension_id);
    printf("VendorExtensionVersion=0x%04X\n", di->vendor_extension_version);
    printf("VendorExtensionDesc=%s\n", di->vendor_extension_description ? di->vendor_extension_description : "");
    printf("FunctionalMode=0x%04X\n", di->functional_mode);
    printf("OperationsSupported:");
    for (i = 0; i < di->operations_len; i++)
        printf(" 0x%04X(%s)", di->operations[i], operation_name(di->operations[i]));
    printf("\nEventsSupported:");
    for (i = 0; i < di->events_len; i++)
        printf(" 0x%04X(UNKNOWN-OR-STANDARD-NEEDS-MAPPING)", di->events[i]);
    printf("\nDevicePropertiesSupported:");
    for (i = 0; i < di->device_properties_len; i++)
        printf(" 0x%04X(UNKNOWN-OR-STANDARD-NEEDS-MAPPING)", di->device_properties[i]);
    printf("\nCaptureFormats:");
    for (i = 0; i < di->capture_formats_len; i++)
        printf(" 0x%04X", di->capture_formats[i]);
    printf("\nImageFormats:");
    for (i = 0; i < di->image_formats_len; i++)
        printf(" 0x%04X", di->image_formats[i]);
    printf("\nManufacturer=%s\n", di->manufacturer ? di->manufacturer : "UNKNOWN");
    printf("Model=%s\n", di->model ? di->model : "UNKNOWN");
    printf("DeviceVersion=%s\n", di->device_version ? di->device_version : "UNKNOWN");
    printf("SerialNumber=<REDACTED>\n");
}

#if P510_ALLOW_USB
static int find_ptp_interface(libusb_device *device,
                              libusb_device_handle **handle,
                              uint8_t *interface_number,
                              uint8_t *bulk_in,
                              uint8_t *bulk_out,
                              uint8_t *interrupt)
{
    libusb_device_handle *candidate;
    struct libusb_config_descriptor *config;
    struct libusb_device_descriptor usb_desc;
    int rc = libusb_get_device_descriptor(device, &usb_desc);
    if (rc != 0)
        return 0;
    if (usb_desc.idVendor != P510_VID || usb_desc.idProduct != P510_PID)
        return 0;

    rc = libusb_get_active_config_descriptor(device, &config);
    if (rc != 0)
        return 0;

    for (uint8_t i = 0; i < config->bNumInterfaces; i++) {
        const struct libusb_interface *iface = &config->interface[i];
        for (int a = 0; a < iface->num_altsetting; a++) {
            const struct libusb_interface_descriptor *alt = &iface->altsetting[a];
            if (alt->bInterfaceClass != P510_PTP_INTERFACE_CLASS ||
                alt->bInterfaceSubClass != P510_PTP_INTERFACE_SUBCLASS ||
                alt->bInterfaceProtocol != P510_PTP_INTERFACE_PROTOCOL)
                continue;

            uint8_t found_in = 0;
            uint8_t found_out = 0;
            uint8_t found_interrupt = 0;
            for (int e = 0; e < alt->bNumEndpoints; e++) {
                const struct libusb_endpoint_descriptor *ep = &alt->endpoint[e];
                if ((ep->bmAttributes & 0x03u) == LIBUSB_TRANSFER_TYPE_BULK) {
                    if ((ep->bEndpointAddress & LIBUSB_ENDPOINT_IN) && !found_in)
                        found_in = ep->bEndpointAddress;
                    if (!(ep->bEndpointAddress & LIBUSB_ENDPOINT_IN) && !found_out)
                        found_out = ep->bEndpointAddress;
                } else if ((ep->bmAttributes & 0x03u) == LIBUSB_TRANSFER_TYPE_INTERRUPT) {
                    found_interrupt = ep->bEndpointAddress;
                }
            }
            if (found_in && found_out) {
                rc = libusb_open(device, &candidate);
                if (rc == 0) {
                    *handle = candidate;
                    *interface_number = alt->bInterfaceNumber;
                    *bulk_in = found_in;
                    *bulk_out = found_out;
                    *interrupt = found_interrupt;
                    libusb_free_config_descriptor(config);
                    return 1;
                }
            }
        }
    }
    libusb_free_config_descriptor(config);
    return 0;
}

static int save_raw_file(const uint8_t *data, size_t size)
{
    FILE *file = fopen("P510-GetDeviceInfo.raw.bin", "wb");
    if (!file)
        return 0;
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

static int execute_get_device_info(libusb_device_handle *handle,
                                   uint8_t interface_number,
                                   uint8_t bulk_in,
                                   uint8_t bulk_out)
{
    uint8_t command[12];
    uint8_t packet[1024];
    uint8_t *raw = NULL;
    size_t raw_size = 0;
    size_t command_len;
    unsigned operation_count = 0;
    int transferred = 0;
    int response_received = 0;
    uint16_t response_code = 0;
    int rc;

    if (operation_count >= P510_OPERATION_LIMIT)
        return 1;
    operation_count++;
    if (operation_count != 1)
        return 1;

    rc = libusb_claim_interface(handle, interface_number);
    if (rc != 0) {
        fprintf(stderr, "Refusing: could not claim PTP interface: %s\n", libusb_error_name(rc));
        return 1;
    }

    command_len = build_get_device_info_command(command);
    printf("OperationCount=%u\n", operation_count);
    printf("OutgoingContainerLength=%zu\n", command_len);
    printf("OutgoingContainerType=0x%04X\n", PTP_CONTAINER_COMMAND);
    printf("OutgoingOperation=0x%04X\n", PTP_OC_GET_DEVICE_INFO);
    printf("OutgoingTransactionID=%u\n", PTP_TRANSACTION_ID);
    printf("SessionID=%u\n", PTP_SESSION_ID);
    print_command_bytes(command, command_len);

    rc = libusb_bulk_transfer(handle, bulk_out, command, (int)command_len, &transferred, 5000);
    if (rc != 0 || transferred != (int)command_len) {
        fprintf(stderr, "GetDeviceInfo command transfer failed: %s\n", libusb_error_name(rc));
        libusb_release_interface(handle, interface_number);
        return 1;
    }

    raw = calloc(1, 1024 * 1024);
    if (!raw) {
        libusb_release_interface(handle, interface_number);
        return 1;
    }

    for (;;) {
        memset(packet, 0, sizeof(packet));
        rc = libusb_bulk_transfer(handle, bulk_in, packet, (int)sizeof(packet), &transferred, 10000);
        if (rc != 0 || transferred < 12)
            break;

        uint32_t container_len = read_u32le(packet);
        uint16_t container_type = read_u16le(packet + 4);
        uint16_t container_code = read_u16le(packet + 6);
        uint32_t transaction_id = read_u32le(packet + 8);
        printf("ReceivedContainerLength=%u Type=0x%04X Code=0x%04X TransactionID=%u\n",
               container_len, container_type, container_code, transaction_id);

        if (transaction_id != PTP_TRANSACTION_ID) {
            fprintf(stderr, "Refusing: unexpected transaction ID\n");
            free(raw);
            libusb_release_interface(handle, interface_number);
            return 1;
        }

        if (container_type == PTP_CONTAINER_RESPONSE) {
            if (container_len != PTP_CONTAINER_HEADER_LEN ||
                container_len != (uint32_t)transferred) {
                fprintf(stderr, "Refusing: malformed PTP response container length\n");
                free(raw);
                libusb_release_interface(handle, interface_number);
                return 1;
            }
            if (container_code == PTP_RESPONSE_OK)
                printf("PTPResponse=0x%04X OK\n", container_code);
            else
                printf("PTPResponse=0x%04X\n", container_code);
            response_received = 1;
            response_code = container_code;
            break;
        }

        if (container_type != PTP_CONTAINER_DATA ||
            container_code != PTP_OC_GET_DEVICE_INFO ||
            container_len < PTP_CONTAINER_HEADER_LEN ||
            container_len > (uint32_t)transferred ||
            raw_size + container_len - PTP_CONTAINER_HEADER_LEN > 1024 * 1024) {
            fprintf(stderr, "Refusing: unexpected PTP data container\n");
            free(raw);
            libusb_release_interface(handle, interface_number);
            return 1;
        }

        size_t payload_len = container_len - PTP_CONTAINER_HEADER_LEN;
        memcpy(raw + raw_size, packet + PTP_CONTAINER_HEADER_LEN, payload_len);
        raw_size += payload_len;
    }

    if (!response_received || response_code != PTP_RESPONSE_OK) {
        fprintf(stderr, "GetDeviceInfo did not receive PTP_OK response\n");
        free(raw);
        libusb_release_interface(handle, interface_number);
        return 1;
    }
    if (!raw_size) {
        fprintf(stderr, "GetDeviceInfo returned no raw data\n");
        free(raw);
        libusb_release_interface(handle, interface_number);
        return 1;
    }
    if (!save_raw_file(raw, raw_size)) {
        fprintf(stderr, "Could not save P510-GetDeviceInfo.raw.bin\n");
        free(raw);
        libusb_release_interface(handle, interface_number);
        return 1;
    }

    P510DeviceInfo di;
    if (parse_device_info(raw, raw_size, &di)) {
        print_device_info(&di);
        free_device_info(&di);
    } else {
        fprintf(stderr, "Raw DeviceInfo parser rejected the response\n");
        free(raw);
        libusb_release_interface(handle, interface_number);
        return 1;
    }
    free(raw);
    libusb_release_interface(handle, interface_number);
    return 0;
}
#endif

static int offline_validate(void)
{
    uint8_t command[12];
    uint8_t fixture[512];
    P510DeviceInfo di;
    size_t command_len = build_get_device_info_command(command);
    size_t offset;
    if (read_u32le(command) != 12u ||
        read_u16le(command + 4) != PTP_CONTAINER_COMMAND ||
        read_u16le(command + 6) != PTP_OC_GET_DEVICE_INFO ||
        read_u32le(command + 8) != PTP_TRANSACTION_ID)
        return 1;

    memset(fixture, 0, sizeof(fixture));
    write_u16le(fixture + 0, 100);
    write_u32le(fixture + 2, 0xFFFFFFFFu);
    write_u16le(fixture + 6, 100);
    offset = 8;
    fixture[offset++] = 1;
    fixture[offset++] = 'X';
    fixture[offset++] = 0;
    write_u16le(fixture + offset, 0);
    offset += 2;

    write_u32le(fixture + offset, 2);
    offset += 4;
    write_u16le(fixture + offset, PTP_OC_GET_DEVICE_INFO);
    offset += 2;
    write_u16le(fixture + offset, 0x1002);
    offset += 2;

    write_u32le(fixture + offset, 0);
    offset += 4;
    write_u32le(fixture + offset, 0);
    offset += 4;
    write_u32le(fixture + offset, 0);
    offset += 4;
    write_u32le(fixture + offset, 1);
    offset += 4;
    write_u16le(fixture + offset, 0x3801);
    offset += 2;
    write_u32le(fixture + offset, 1);
    offset += 4;
    write_u16le(fixture + offset, 0x3801);
    offset += 2;

    if (parse_device_info(fixture, offset, &di)) {
        printf("Synthetic DeviceInfo fixture (not physical camera data):\n");
        print_device_info(&di);
        free_device_info(&di);
    } else {
        fprintf(stderr, "Offline fixture parse failed\n");
        return 1;
    }

    printf("COMPILED TARGET CONFIGURATION\n");
    printf("Target VID: 0x%04X\n", P510_VID);
    printf("Target PID: 0x%04X\n", P510_PID);
    printf("Required USB interface class: 0x%02X\n", P510_PTP_INTERFACE_CLASS);
    printf("Required USB interface subclass: 0x%02X\n", P510_PTP_INTERFACE_SUBCLASS);
    printf("Required USB interface protocol: 0x%02X\n", P510_PTP_INTERFACE_PROTOCOL);
    printf("Allowed PTP operation: 0x%04X GetDeviceInfo\n", PTP_OC_GET_DEVICE_INFO);
    printf("Maximum PTP operations: %u\n", P510_OPERATION_LIMIT);
#if P510_ALLOW_USB
    printf("USB hardware support: ENABLED\n");
#else
    printf("USB hardware support: DISABLED\n");
#endif

    printf("\nPHYSICAL DEVICE OBSERVATION\n");
    printf("Physical device observation: NONE (dry-run)\n");
    printf("Physical USB enumeration performed: NO\n");
    printf("Physical USB device opened: NO\n");
    printf("Physical interface claimed: NO\n");
    printf("USB transfer performed: NO\n");

    printf("OperationCount=1\n");
    printf("OutgoingContainerLength=%zu\n", command_len);
    printf("OutgoingContainerType=0x%04X\n", PTP_CONTAINER_COMMAND);
    printf("OutgoingOperation=0x%04X\n", PTP_OC_GET_DEVICE_INFO);
    printf("OutgoingTransactionID=%u\n", PTP_TRANSACTION_ID);
    printf("SessionID=%u\n", PTP_SESSION_ID);
    print_command_bytes(command, command_len);
    return 0;
}

int main(int argc, char **argv)
{
    /* P510_ALLOW_USB is reserved for a separately approved hardware build. */
    if (argc == 2 && strcmp(argv[1], "--dry-run") == 0)
        return offline_validate();
    if (argc != 1) {
        fprintf(stderr, "Usage: %s [--dry-run]\n", argv[0]);
        return 2;
    }

#if P510_ALLOW_USB
    libusb_context *context = NULL;
    libusb_device **devices = NULL;
    libusb_device_handle *handle = NULL;
    uint8_t interface_number = 0;
    uint8_t bulk_in = 0;
    uint8_t bulk_out = 0;
    uint8_t interrupt = 0;
    ssize_t count;
    ssize_t i;
    unsigned matches = 0;
    int rc = libusb_init(&context);
    if (rc != 0)
        return 2;

    count = libusb_get_device_list(context, &devices);
    if (count < 0) {
        libusb_exit(context);
        return 2;
    }
    for (i = 0; i < count; i++) {
        struct libusb_device_descriptor descriptor;
        if (libusb_get_device_descriptor(devices[i], &descriptor) == 0 &&
            descriptor.idVendor == P510_VID &&
            descriptor.idProduct == P510_PID) {
            matches++;
            if (matches == 1) {
                if (!find_ptp_interface(devices[i], &handle, &interface_number,
                                         &bulk_in, &bulk_out, &interrupt))
                    matches = 2;
            }
        }
    }
    libusb_free_device_list(devices, 1);
    if (matches != 1 || handle == NULL ||
        bulk_in == 0 || bulk_out == 0) {
        if (handle)
            libusb_close(handle);
        libusb_exit(context);
        fprintf(stderr, "Refusing: expected exactly one 04B0:0223 Still Image/PTP interface\n");
        return 2;
    }

    printf("USBDeviceSelected=04B0:0223\n");
    printf("InterfaceSelected=%u\n", interface_number);
    printf("BulkIN=0x%02X\n", bulk_in);
    printf("BulkOUT=0x%02X\n", bulk_out);
    printf("InterruptEndpoint=0x%02X\n", interrupt);
    rc = execute_get_device_info(handle, interface_number, bulk_in, bulk_out);
    libusb_close(handle);
    libusb_exit(context);
    return rc;
#else
    return offline_validate();
#endif
}
