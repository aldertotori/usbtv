#include "usbtv.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject,PUNICODE_STRING RegistryPath);
NTSTATUS DispatchNull(PDEVICE_OBJECT DeviceObject,PIRP Irp);
NTSTATUS DispatchIoCtl(PDEVICE_OBJECT DeviceObject,PIRP Irp);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);

NTSTATUS DeviceAdd(IN PKSDEVICE Device);
NTSTATUS DeviceStart(IN PKSDEVICE Device);
NTSTATUS DeviceStop(IN PKSDEVICE Device);
NTSTATUS DeviceRemove(IN PKSDEVICE Device);
NTSTATUS DeviceSurpriseRemove(IN PKSDEVICE Device);
NTSTATUS DeviceSetPower(IN PKSDEVICE Device);



#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, DriverUnload)
#pragma alloc_text (PAGE, DispatchNull)
#pragma alloc_text (PAGE, DispatchIoCtl)
#endif


LPWSTR	registryPath	= 0;
ULONG	registryLength	= 0;
KSDEVICE_DISPATCH	Dispatch = 
{
	DeviceAdd,
	DeviceStart,
	0,
	0,
	0,
	DeviceStop,
	0,
	0,
	DeviceRemove,
	0,
	DeviceSurpriseRemove,
	0,
	DeviceSetPower,
	0
};

KSDEVICE_DESCRIPTOR	Descriptor = 
{
	&Dispatch,
	0,
	0,
	KSDEVICE_DESCRIPTOR_VERSION
};


NTSTATUS  DriverEntry(PDRIVER_OBJECT DriverObject,PUNICODE_STRING RegistryPath)
{
	NTSTATUS			Status = STATUS_SUCCESS;

	PAGED_CODE();

	Status = KsInitializeDriver(DriverObject,RegistryPath,&Descriptor);

	registryLength = RegistryPath->Length  + 2;

	registryPath = ExAllocatePoolWithTag(NonPagedPool,
					RegistryPath->Length + 2,
					POOL_TAG);

	RtlZeroMemory(registryPath,registryLength);

	RtlCopyMemory(registryPath,RegistryPath->Buffer,RegistryPath->Length);

	return Status;
}

NTSTATUS DispatchIoCtl(PDEVICE_OBJECT DeviceObject,PIRP Irp)
{
	PDEVICE_EXTENSION	DevExt;
	PIO_STACK_LOCATION	IrpSp;
	
	PAGED_CODE();
	
	IrpSp = IoGetCurrentIrpStackLocation(Irp);
	DevExt = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;

	switch(IrpSp->Parameters.DeviceIoControl.IoControlCode)
	{
		
		
	default:
		break;
	}

	IoCompleteRequest(Irp,0);
	return STATUS_SUCCESS;
}

NTSTATUS DispatchNull(PDEVICE_OBJECT DeviceObject,PIRP Irp)
{
	PDEVICE_EXTENSION	DevExt;
	PIO_STACK_LOCATION	IrpSp;

	PAGED_CODE();

	IrpSp = IoGetCurrentIrpStackLocation(Irp);
	DevExt = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;


	IoCompleteRequest(Irp,0);
	return STATUS_SUCCESS;
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING	SymbolicName;
	PAGED_CODE();

	RtlInitUnicodeString(&SymbolicName,DOS_DEVICE_NAME);
	IoDeleteSymbolicLink(&SymbolicName);
	IoDeleteDevice(DriverObject->DeviceObject);
	
}

