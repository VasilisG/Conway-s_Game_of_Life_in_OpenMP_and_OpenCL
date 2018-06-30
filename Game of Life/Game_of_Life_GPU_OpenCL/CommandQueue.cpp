#include "CommandQueue.h"

cl_command_queue createCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties)
{
    cl_int errcode;

    cl_command_queue commandQueue = clCreateCommandQueue(context, device, properties, &errcode);

    switch(errcode)
    {
    case CL_SUCCESS:
        printf("Successfully created command queue.\n");
        break;

    case CL_INVALID_CONTEXT:
        printf("Failed to create command queue. Invalid context.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_DEVICE:
        printf("Failed to create command queue. Invalid device or device not associated with context.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Failed to create command queue. Invalid properties.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_QUEUE_PROPERTIES:
        printf("Failed to create command queue. Some properties may not be supported by selected device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Failed to create context. Could not allocate resource on the host.\n");
        exit(EXIT_FAILURE);
    }

    return commandQueue;
}

void finish(cl_command_queue command_queue)
{
    cl_int result = clFinish(command_queue);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void releaseCommandQueue(cl_command_queue commandQueue)
{
    cl_int result = clReleaseCommandQueue(commandQueue);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Released command queue.\n");
        break;

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue.n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

