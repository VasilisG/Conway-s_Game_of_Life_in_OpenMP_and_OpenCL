#include "Kernel.h"

cl_kernel createKernel(cl_program program, const char *kernel_name)
{
    cl_kernel kernel;
    cl_int result;

    kernel = clCreateKernel(program, kernel_name, &result);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Successfully created kernel object.\n");
        break;

    case CL_INVALID_PROGRAM:
        printf("Error: Invalid program object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_PROGRAM_EXECUTABLE:
        printf("Error: There is no successfully built executable for program object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_KERNEL_NAME:
        printf("Error: Kernel name not found in program object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_KERNEL_DEFINITION:
        printf("Error: Kernel definition is not the same for all devices for which the program executable has been built.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Kernel name is NULL.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }

    return kernel;
}

void getKernelArgumentCountlInfo(cl_kernel kernel)
{
    uint kernelArgCount = 0;
    cl_int result = clGetKernelInfo(kernel, CL_KERNEL_NUM_ARGS, sizeof(kernelArgCount), &kernelArgCount, 0);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Number of kernel arguments: %d\n", kernelArgCount);
        break;

    case CL_INVALID_VALUE:
        printf("Error: Invalid information parameter or insufficient buffer size to store kernel information.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_KERNEL:
        printf("Error: Kernel is not a valid object.\n");
        exit(EXIT_FAILURE);
    }
}

void setKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value)
{
    cl_int result = clSetKernelArg(kernel, arg_index, arg_size, arg_value);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Added argument to kernel.\n");
        break;

    case CL_INVALID_KERNEL:
        printf("Error: Invalid kernel object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_ARG_INDEX:
        printf("Error: Invalid argument index. (Must fit with the index in kernel's declaration)\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_ARG_VALUE:
        printf("Error: Argument value is NULL.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MEM_OBJECT:
        printf("Error: Argument value is not a valid memory object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_SAMPLER:
        printf("Error: Argument value is not a valid sampler object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_ARG_SIZE:
        printf("Error: Argument size does not match the size of a datatype.\n");
        exit(EXIT_FAILURE);
    }
}

void releaseKernel(cl_kernel kernel)
{
    cl_int result = clReleaseKernel(kernel);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Kernel released.\n");
        break;

    case CL_INVALID_KERNEL:
        printf("Error: Invalid kernel object.\n");
        exit(EXIT_FAILURE);
    }
}

