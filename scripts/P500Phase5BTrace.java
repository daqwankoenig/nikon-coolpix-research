import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.mem.Memory;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class P500Phase5BTrace extends GhidraScript {
    // This script changes only the open Ghidra program listing; run it on a disposable project copy.
    private static final String[][] STRINGS = {
        {"STATUS READ ERROR", "0x6147D0"},
        {"BUFFER SIZE ERROR", "0x6147F8"},
        {"RAW READ ERROR", "0x614818"},
        {"STATUS FOLDER READ ERROR", "0x614838"},
        {"STATUS FILE READ ERROR", "0x614860"},
        {"RGB READ ERROR", "0x614888"},
        {"RAW filename token", "0x6148A8"},
        {"RAW filename token duplicate", "0x6148AC"},
        {"RAW DATA filename format", "0x6148B0"},
        {"JPEG extension entry", "0x605EFC"},
        {"NEF extension entry", "0x605F1C"},
        {"TIFF extension entry", "0x6465F8"},
        {"MOV extension entry", "0x646600"},
        {"AVI extension entry", "0x646608"},
        {"JPEG extension entry 2", "0x646610"},
        {"sample JPEG filename", "0x61B994"},
        {"RAW file-type entry", "0x649418"},
        {"NEF file-type entry", "0x649420"},
        {"NRW file-type entry", "0x649424"},
        {"RAW_MODE", "0x666D78"},
        {"RAW acquisition size", "0x666F40"},
        {"Process NRW (RAW) photos", "0x6E6E30"},
        {"NRW + Basic", "0x6EA87C"},
        {"NRW + Fine", "0x6F0984"},
        {"NRW + Normal", "0x6F09A8"},
        {"NRW processing", "0x6F0B04"},
        {"Create JPEG copy", "0x6F0B8C"},
        {"create JPEG copies", "0x6F0BC4"}
    };

    private static final String[][] CODE = {
        {"RAW diagnostic routine candidate", "0x1CF870"},
        {"RAW diagnostic second prologue", "0x1CF8B8"},
        {"RAW error literal load", "0x1CF984"},
        {"RAW error literal pool", "0x1CFC10"},
        {"RAW diagnostic helper candidate", "0x1CFC40"},
        {"RAW error callee", "0x537BB0"},
        {"RAW_MODE reference", "0x565334"},
        {"acquisition-size reference", "0x565748"},
        {"RAW routine tail", "0x1CFBA0"},
        {"RAW routine second entry", "0x1CFAF0"},
        {"buffer helper", "0x2DF08C"},
        {"buffer release helper", "0x2DF0B0"},
        {"buffer copy helper", "0x2DF0C4"},
        {"generic API A", "0x2DF0E0"},
        {"generic API target A", "0x49F268"},
        {"generic API target B", "0x49F304"},
        {"generic API target C", "0x4A14B0"},
        {"generic API target D", "0x49F468"},
        {"extension-table consumer", "0x3AEC40"},
        {"RAW file-type table consumer", "0x4A24F8"},
        {"sample JPEG filename consumer", "0x29B774"},
        {"dimension helper", "0x86314"},
        {"indexed-size helper A", "0x8665C"},
        {"indexed-size helper B", "0x86708"},
        {"format copy helper", "0x537B28"},
        {"format engine", "0x537704"},
        {"acquisition record helper", "0x1BFD6C"}
    };

    private Listing listing;
    private ReferenceManager references;
    private DecompInterface decompiler;

    @Override
    public void run() throws Exception {
        listing = currentProgram.getListing();
        references = currentProgram.getReferenceManager();
        decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);

        println("PROGRAM=" + currentProgram.getName());
        println("LANGUAGE=" + currentProgram.getLanguage().getLanguageID());
        println("IMAGE_BASE=" + currentProgram.getImageBase());

        String[] disassemblyStarts = {
            "0x1CF870", "0x1CF8B8", "0x1CF9AC", "0x1CF9D4",
            "0x1CF9FC", "0x1CFAAC", "0x1CFB00", "0x1CFB10",
            "0x1CFBA0", "0x1CFAF0", "0x1CFBC0", "0x1CF190", "0x1CF860",
            "0x1CFC40", "0x537BB0", "0x2DF08C", "0x2DF0B0",
            "0x2DF0C4", "0x2DF0E0", "0x49F268", "0x49F304",
            "0x4A14B0", "0x49F468", "0x3AEC40", "0x4A24F8",
            "0x29B774", "0x1CFA38", "0x86314",
            "0x8665C", "0x86708", "0x537B28", "0x537704",
            "0x1BFD6C", "0x565334", "0x565748"
        };
        for (String start : disassemblyStarts) {
            Address address = toAddr(start);
            println("DISASSEMBLE " + address + " result=" + disassemble(address));
        }

        for (String[] item : STRINGS) {
            Address address = toAddr(item[1]);
            println("\nSTRING " + item[0] + " @ " + address);
            dumpReferences(address);
        }

        scanLiteralReferences();

        for (String[] item : CODE) {
            Address address = toAddr(item[1]);
            println("\nCODE " + item[0] + " @ " + address);
            Instruction direct = listing.getInstructionAt(address);
            println("  DIRECT_INSTRUCTION " + (direct == null ? "<none>" : direct.toString()));
            Function function = listing.getFunctionContaining(address);
            if (function == null) {
                dumpReferences(address);
                if (item[0].equals("RAW error literal load")) {
                    dumpWindow(address, 0x100, 0x200);
                } else if (item[0].equals("RAW_MODE reference")) {
                    dumpWindow(address, 0x60, 0x1A0);
                } else if (item[0].equals("acquisition-size reference")) {
                    dumpWindow(address, 0x60, 0x2B0);
                } else {
                    dumpWindow(address, 0x60, 0x90);
                }
            } else {
                dumpFunction(function);
            }
        }

        dumpStringPool(toAddr("0x1CFC10"), 16);
        dumpStringPool(toAddr("0x565D90"), 16);
        dumpStringPool(toAddr("0x565E00"), 12);
        scanArmCallsTo(toAddr("0x1CF8B8"));
        scanArmCallsTo(toAddr("0x1CFA38"));
        scanArmCallsTo(toAddr("0x1CFAF0"));
        scanArmCallsTo(toAddr("0x86314"));
        scanArmCallsTo(toAddr("0x2DF08C"));
        scanArmCallsTo(toAddr("0x2DF0B0"));
        scanArmCallsTo(toAddr("0x2DF0E0"));
    }

    private void scanLiteralReferences() throws Exception {
        Map<Long, List<String>> stringsByOffset = new HashMap<>();
        for (String[] item : STRINGS) {
            long offset = Long.decode(item[1]);
            stringsByOffset.computeIfAbsent(offset, key -> new ArrayList<>()).add(item[0]);
        }

        Memory memory = currentProgram.getMemory();
        AddressSpace space = currentProgram.getAddressFactory().getDefaultAddressSpace();
        long lastWord = currentProgram.getMaxAddress().getOffset() - 3;
        Map<Long, List<String>> pools = new HashMap<>();
        for (long offset = 0; offset <= lastWord; offset += 4) {
            long value = Integer.toUnsignedLong(memory.getInt(space.getAddress(offset)));
            List<String> labels = stringsByOffset.get(value);
            if (labels != null) {
                pools.put(offset, labels);
                println("OFFSET_WORD pool=0x" + Long.toHexString(offset) +
                    " strings=" + labels);
            }
        }

        for (long offset = 0; offset <= lastWord; offset += 4) {
            int instruction = memory.getInt(space.getAddress(offset));
            if ((instruction & 0x0F7F0000) != 0x051F0000) {
                continue;
            }

            long immediate = instruction & 0xFFF;
            long pool = offset + 8 +
                (((instruction & 0x00800000) != 0) ? immediate : -immediate);
            List<String> labels = pools.get(pool);
            if (labels != null) {
                println("LDR_LITERAL site=0x" + Long.toHexString(offset) +
                    " pool=0x" + Long.toHexString(pool) +
                    " instruction=0x" + Integer.toHexString(instruction) +
                    " strings=" + labels);
            }
        }
    }

    private void scanArmCallsTo(Address target) throws Exception {
        Memory memory = currentProgram.getMemory();
        AddressSpace space = currentProgram.getAddressFactory().getDefaultAddressSpace();
        long lastWord = currentProgram.getMaxAddress().getOffset() - 3;
        println("\nARM BL candidates to " + target);
        int count = 0;
        for (long offset = 0; offset <= lastWord; offset += 4) {
            int instruction = memory.getInt(space.getAddress(offset));
            if ((instruction & 0x0F000000) != 0x0B000000) {
                continue;
            }
            long displacement = (long) ((instruction << 8) >> 6);
            long destination = offset + 8 + displacement;
            if (destination == target.getOffset()) {
                println("  site=0x" + Long.toHexString(offset) +
                    " word=0x" + Integer.toHexString(instruction));
                count++;
            }
        }
        println("  candidate_count=" + count);
    }

    private void dumpReferences(Address address) {
        ReferenceIterator iterator = references.getReferencesTo(address);
        int count = 0;
        while (iterator.hasNext() && count < 80) {
            Reference reference = iterator.next();
            println("  REF " + reference.getFromAddress() + " -> " +
                reference.getToAddress() + " [" + reference.getReferenceType() + "]");
            count++;
        }
        if (iterator.hasNext()) {
            println("  References truncated after 80 entries.");
        }
        if (count == 0) {
            println("  No Ghidra references recorded.");
        }
    }

    private void dumpStringPool(Address start, int words) throws Exception {
        println("\nLITERAL POOL near " + start);
        for (int i = 0; i < words; i++) {
            Address slot = start.add(i * 4L);
            long value = Integer.toUnsignedLong(currentProgram.getMemory().getInt(slot));
            String text = readAscii(value, 96);
            println("  " + slot + " -> 0x" + Long.toHexString(value) +
                (text.isEmpty() ? "" : " \"" + text + "\""));
        }
    }

    private String readAscii(long offset, int limit) throws Exception {
        Address address = currentProgram.getAddressFactory().getDefaultAddressSpace()
            .getAddress(offset);
        if (!currentProgram.getMemory().contains(address)) {
            return "";
        }

        StringBuilder text = new StringBuilder();
        for (int i = 0; i < limit; i++) {
            Address characterAddress = address.add(i);
            if (!currentProgram.getMemory().contains(characterAddress)) {
                return "";
            }
            int value = Byte.toUnsignedInt(currentProgram.getMemory().getByte(characterAddress));
            if (value == 0 || value == '\r' || value == '\n') {
                break;
            }
            if (value < 0x20 || value > 0x7e) {
                return "";
            }
            text.append((char) value);
        }
        return text.toString();
    }

    private void dumpFunction(Function function) {
        println("FUNCTION " + function.getName() + " @ " + function.getEntryPoint() +
            " body=" + function.getBody().getNumAddresses() + " bytes");
        dumpReferences(function.getEntryPoint());

        InstructionIterator iterator = listing.getInstructions(function.getBody(), true);
        int count = 0;
        while (iterator.hasNext() && count < 600) {
            Instruction instruction = iterator.next();
            println("  " + instruction.getAddress() + ": " + instruction);
            count++;
        }
        if (iterator.hasNext()) {
            println("  Instruction output truncated at 600 instructions.");
        }

        DecompileResults result = decompiler.decompileFunction(function, 45, monitor);
        if (result.decompileCompleted()) {
            println("DECOMPILED " + function.getName() + ":\n" +
                result.getDecompiledFunction().getC());
        } else {
            println("DECOMPILATION FAILED for " + function.getName() + ": " +
                result.getErrorMessage());
        }
    }

    private void dumpWindow(Address center, long before, long after) {
        Address start = center.subtract(before);
        Address end = center.add(after);
        AddressSetView set = currentProgram.getMemory().getLoadedAndInitializedAddressSet();
        if (!set.contains(start) || !set.contains(end)) {
            println("  Requested window is not fully within initialized memory.");
            return;
        }

        InstructionIterator iterator =
            listing.getInstructions(new AddressSet(start, end), true);
        int count = 0;
        while (iterator.hasNext() && count < 160) {
            Instruction instruction = iterator.next();
            println("  " + instruction.getAddress() + ": " + instruction);
            count++;
        }
        if (count == 0) {
            println("  No instructions recorded in this window.");
        }
    }
}
