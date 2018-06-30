#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

/* Functions that wrap OpenCL command queue functions. */
cl_command_queue createCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties);
void finish(cl_command_queue command_queue);
void releaseCommandQueue(cl_command_queue commandQueue);

#endif // COMMAND_QUEUE_H
