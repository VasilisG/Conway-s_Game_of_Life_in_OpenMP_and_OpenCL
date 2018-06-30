#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

/* Functions that wrap OpenCL program object functions. */
cl_program createProgramWithSource(cl_context context, const char **kernelSource, const size_t *kernelLength);
void buildProgram(cl_program program, cl_uint num_devices, const cl_device_id *device_list, const char *options);
void getProgramBuildInfo(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
void getProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
void releaseProgram(cl_program program);

#endif // PROGRAM_H
