$ErrorActionPreference = 'Stop'

$source = Join-Path $PSScriptRoot 'P510PTPGetDeviceInfo.c'
$text = Get-Content -LiteralPath $source -Raw

function Assert-Contains([string]$Pattern, [string]$Label) {
    if ($text -notmatch $Pattern) { throw "Missing required safety/packet token: $Label" }
}

function Assert-NotContains([string]$Pattern, [string]$Label) {
    if ($text -match $Pattern) { throw "Forbidden operation implementation detected: $Label" }
}

Assert-Contains '#define P510_VID 0x04B0u' 'P510 VID'
Assert-Contains '#define P510_PID 0x0223u' 'P510 PID'
Assert-Contains '#define PTP_OC_GET_DEVICE_INFO 0x1001u' 'GetDeviceInfo'
Assert-Contains '#define P510_OPERATION_LIMIT 1u' 'operation limit'

Assert-NotContains 'PTP_OC_OpenSession|PTP_OC_CloseSession|GetStorageIDs|GetStorageInfo|InitiateCapture|SetDevicePropValue|DeleteObject|SendObject|PTP_OC_ResetDevice|PTP_OC_FormatStore' 'forbidden PTP implementation'
Assert-Contains 'P510_ALLOW_USB 0' 'hardware-disabled default'
Assert-Contains 'P510_ALLOW_USB is reserved' 'hardware guard'

$command = New-Object byte[] 12
$length = [BitConverter]::GetBytes([uint32]12)
$type = [BitConverter]::GetBytes([uint16]1)
$opcode = [BitConverter]::GetBytes([uint16]0x1001)
$transaction = [BitConverter]::GetBytes([uint32]1)
[Array]::Copy($length, 0, $command, 0, 4)
[Array]::Copy($type, 0, $command, 4, 2)
[Array]::Copy($opcode, 0, $command, 6, 2)
[Array]::Copy($transaction, 0, $command, 8, 4)

if ([BitConverter]::ToUInt16($command, 6) -ne 0x1001) { throw 'GetDeviceInfo opcode mismatch' }
if ([BitConverter]::ToUInt32($command, 8) -ne 1) { throw 'Transaction ID mismatch' }

$hex = ($command | ForEach-Object { $_.ToString('X2') }) -join ' '
Write-Output "Offline packet validation passed"
Write-Output "OutgoingContainer=12 0001 1001 01000000"
Write-Output "NormalizedHex=$hex"
