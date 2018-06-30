#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "Globals.h"

/* Functions that wrap OpenCL device functions. */
void getDevices(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id *device, cl_uint *num_devices);
void getDeviceInfo(cl_device_id device, cl_device_info device_info, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
void getAllDeviceInfo(cl_device_id device, size_t param_value_size);

#endif // DEVICE_H
