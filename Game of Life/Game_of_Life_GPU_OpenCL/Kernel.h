#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

typedef unsigned int uint;

/* Functions that wrap OpenCL kernel object functions.*/
cl_kernel createKernel(cl_program program, const char *kernel_name);
void getKernelArgumentCountlInfo(cl_kernel kernel);
void setKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value);
void releaseKernel(cl_kernel kernel);

#endif // KERNEL_H
