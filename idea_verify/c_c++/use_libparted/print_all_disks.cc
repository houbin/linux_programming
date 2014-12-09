#include "parted/parted.h"
#include "parted/device.h"
#include <stdio.h>

int main()
{
	ped_device_probe_all();

	PedDevice *dev = 0;

	while ((dev = ped_device_get_next(dev)))
	{
		printf("=========================================\n");
		printf("device model: %s\n", dev->model);
		printf("path:%s\n", dev->path);
		long long size = (dev->sector_size * dev->length) / (1024 * 1024 * 1024);
		printf("size: %lld G\n", size);
	}

	return 0;
}
