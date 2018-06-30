#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

/* Functions that wrap OpenCL context functions. */
cl_context createContext(const cl_context_properties *prop, cl_uint num_devices, const cl_device_id *devices);
void releaseContext(cl_context context);

#endif // CONTEXT_H
