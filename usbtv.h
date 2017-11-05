#include <ntddk.h>
#include <ks.h>


#define	POOL_TAG	'VTDA'

#define NT_DEVICE_NAME			L"\\Device\\USBTV"
#define DOS_DEVICE_NAME			L"\\DosDevices\\USBTV"

typedef struct _DEVICE_EXTENSION
{
	PDEVICE_OBJECT       Device;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

