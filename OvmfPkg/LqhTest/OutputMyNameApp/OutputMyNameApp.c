/** @file

  Copyright (c) 2006 - 2016, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>

extern EFI_GUID  gLqhTestVariableGuid    = { 0x84fcbe8e, 0x7c48, 0x46f0, { 0x86, 0x5c, 0x9f, 0xc7, 0x95, 0xaf, 0xa1, 0x9d }};

EFI_STATUS
EFIAPI
OutputMyNameApp (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    CHAR8  Myname[10];
    EFI_STATUS  Status;
    UINTN       Size;

    Size = sizeof(Myname);
    Status = gRT->GetVariable (
        L"luqiuhuan",
        &gLqhTestVariableGuid,
        NULL,
        &Size,
        &Myname
        );

    if (EFI_ERROR (Status)) {
        Print(L"gLqhTestVariableGuid-----( %g )\n", &gLqhTestVariableGuid);
        Print(L"OutputMyNameApp: Status = %r\n", Status);
        return Status;
    }
    Print(L"%a\n", *Myname);
    Print(L"luqiuhuan test1.\n");

  return EFI_SUCCESS;
}
