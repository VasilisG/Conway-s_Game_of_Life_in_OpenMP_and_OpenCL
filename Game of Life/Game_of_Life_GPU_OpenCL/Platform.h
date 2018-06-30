#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#include "Globals.h"

/* Functions that wrap OpenCL platform functions. */
void getPlatforms(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms);
void initPlatformAttributes(cl_platform_info attributes[PLATFORM_ATTRIBUTES]);
void showPlatformAttributes(cl_platform_info attributes[PLATFORM_ATTRIBUTES]);
void getPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, char *param_value, size_t *param_value_size_ret);
void getAllPlatformInfo(cl_uint num_platforms, cl_platform_id *platforms, size_t param_value_size, char *param_value, size_t *param_value_size_ret);

#endif // PLATFORM_H

