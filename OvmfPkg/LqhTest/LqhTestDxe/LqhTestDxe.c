#include <uefi.h> 
#include <Library/UefiLib.h> 
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Pi/PiBootMode.h>
#include <Library/HobLib.h>
#include <PiPei.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Uefi/UefiSpec.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PcdLib.h>


extern EFI_GUID  gLqhTestHobGuid         = { 0x78a85cac, 0xe347, 0x44f4, { 0x88, 0x55, 0x72, 0xee, 0x38, 0xe3, 0x76, 0xd9 }};
extern EFI_GUID  gLqhTestVariableGuid    = { 0x84fcbe8e, 0x7c48, 0x46f0, { 0x86, 0x5c, 0x9f, 0xc7, 0x95, 0xaf, 0xa1, 0x9d }};

EFI_STATUS
EFIAPI
LqhTestDxeEntrypoint(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{ 
    EFI_STATUS               Status;
    EFI_PEI_HOB_POINTERS     Hob;
    UINT8                    *HobEnd;

    HobEnd = NULL;
    Hob.Raw   = GetHobList();
    while ((Hob.Raw = GetNextHob(EFI_HOB_TYPE_MEMORY_ALLOCATION, Hob.Raw)) != NULL) {
        if (CompareGuid(&gLqhTestHobGuid, &Hob.MemoryAllocation->AllocDescriptor.Name)) {
	          HobEnd = (Hob.Raw + sizeof (EFI_HOB_GENERIC_HEADER) + 16);
        break;
        }
        Hob.Raw = GET_NEXT_HOB(Hob);
    }
    Status = gRT->SetVariable (
        L"luqiuhuan",
        &gLqhTestVariableGuid,
        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
        sizeof(HobEnd),
        &HobEnd
        );
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "LqhTestDxeEntrypoint:SetVariable Fail.\n"));
        return Status;
    }
    return Status;
}
