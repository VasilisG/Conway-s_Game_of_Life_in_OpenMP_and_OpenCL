#include "Context.h"

cl_context createContext(const cl_context_properties *prop, cl_uint num_devices, const cl_device_id *devices)
{
    cl_int errcode_ret;

    cl_context context = clCreateContext(prop, num_devices, devices, NULL, NULL, &errcode_ret);

    switch(errcode_ret)
    {
    case CL_SUCCESS:
        printf("Successfully created context.\n");
        break;

    case CL_INVALID_PLATFORM:
        printf("Failed to create context. Context properties cannot be set to NULL.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Failed to create context. Invalid context properties.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_DEVICE:
        printf("Failed to create context. Invalid device parameter.\n");
        exit(EXIT_FAILURE);

    case CL_DEVICE_NOT_AVAILABLE:
        printf("Failed to create context. Device not available.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Failed to create context. Could not allocate resource on the host.\n");
        exit(EXIT_FAILURE);
    }

    return context;
}

void releaseContext(cl_context context)
{
    cl_int result = clReleaseContext(context);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Context released.\n");
        break;

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}
