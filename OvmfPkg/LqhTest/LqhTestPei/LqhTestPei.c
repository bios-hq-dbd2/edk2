#include <uefi.h> 
#include <Library/UefiLib.h> 
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Pi/PiHob.h>
#include <Pi/PiPeiCis.h>
#include <Library/PcdLib.h>

extern EFI_GUID  gLqhTestHobGuid = { 0x78a85cac, 0xe347, 0x44f4, { 0x88, 0x55, 0x72, 0xee, 0x38, 0xe3, 0x76, 0xd9 }};

VOID
EfiCommonLibCopyMem (
  IN VOID   *Destination,
  IN VOID   *Source,
  IN UINTN  Length
  )
{
  CHAR8 *Destination8;
  CHAR8 *Source8;

  if (Source < Destination) {
    Destination8  = (CHAR8 *) Destination + Length - 1;
    Source8       = (CHAR8 *) Source + Length - 1;
    while (Length--) {
      *(Destination8--) = *(Source8--);
    }
  } else {
    Destination8 = (CHAR8 *) Destination;
    Source8      = (CHAR8 *) Source;
    while (Length--) {
      *(Destination8++) = *(Source8++);
    }
  }
}

EFI_STATUS
EFIAPI
LqhTestPeiEntrypoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
)
{ 
    DEBUG ((EFI_D_ERROR, "LqhTestPeiEntrypoint:PeiServicesCreateHob star.\n"));

    EFI_STATUS  Status;
    CHAR8       *LlqhTestHob = NULL;
    CHAR8       *LlqhTestHobEnd = NULL;
    CHAR16      StrMyname[] = L"luqiuhuan";

    PeiServices = GetPeiServicesTablePointer();
    Status = PeiServicesCreateHob (
        EFI_HOB_TYPE_MEMORY_ALLOCATION,
        64,
        &LlqhTestHob
        );
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "LqhTestPeiEntrypoint:PeiServicesCreateHob Fail.\n"));
        return Status;
    }
    
    LlqhTestHobEnd = (LlqhTestHob + sizeof (EFI_HOB_GENERIC_HEADER));  // All HOBs must contain this generic HOB header
    EfiCommonLibCopyMem(LlqhTestHobEnd, &gLqhTestHobGuid, sizeof(gLqhTestHobGuid)); // guid
    EfiCommonLibCopyMem(LlqhTestHobEnd+16,StrMyname,2*10);  // string
    return Status;
}
