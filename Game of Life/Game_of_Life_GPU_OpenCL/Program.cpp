#include "Program.h"

cl_program createProgramWithSource(cl_context context, const char **kernelSource, const size_t *kernelLength)
{
    cl_int result;
    cl_program program;

    program = clCreateProgramWithSource(context, 1, kernelSource, kernelLength, &result);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Program created with kernel source.\n");
        break;

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid kernel source (possibly NULL line in source).\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Could not allocate resources for the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Could not allocate resource for the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }

    return program;
}

void buildProgram(cl_program program, cl_uint num_devices, const cl_device_id *device_list, const char *options)
{
    cl_int result = clBuildProgram(program, num_devices, device_list, options, NULL, NULL);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Program successfully built.\n");
        break;

    case CL_INVALID_VALUE:
        printf("Error: \'device_list\' is NULL and \'num_devices\' is greater than 0, or \'device_list\' is not NULL and \'num_devices\' is 0.");
        exit(EXIT_FAILURE);

    case CL_INVALID_DEVICE:
        printf("Error: OpenCL devices listed in \'device_list\' are not in the list of devices associated with \'program\'.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_BINARY:
        printf("Error: Devices listed in \'device_list\' do not have a valid program binary loaded.");
        exit(EXIT_FAILURE);

    case CL_INVALID_BUILD_OPTIONS:
        printf("Error: Invalid build options.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_OPERATION:
        printf("Error: Program executable build for any of the devices listed in \'device_list\' by a previous call to \'BuildProgram\' for \'program\' has not completed.\n");
        exit(EXIT_FAILURE);

    case CL_COMPILER_NOT_AVAILABLE:
        printf("Error: Compiler not available.\n");
        exit(EXIT_FAILURE);

    case CL_BUILD_PROGRAM_FAILURE:
        printf("Error: Failed to build the program executable.\n");
        break;
        //size_t logSize;
        //clGetProgramBuildInfo(program, device_list[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        //char *log = (char *)malloc(logSize);
        //clGetProgramBuildInfo(program, device_list[0], CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void getProgramBuildInfo(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
{
    cl_int result = clGetProgramBuildInfo(program, device, param_name, param_value_size, param_value, param_value_size_ret);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_DEVICE:
        printf("Error: Device is not in the list of devices associated with the program.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid parameter value or insufficient buffer size to store build information.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_PROGRAM:
        printf("Error: Invalid program object parameter.\n");
        exit(EXIT_FAILURE);
    }
}

void getProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
{
    cl_int result = clGetProgramInfo(program, param_name, param_value_size, param_value, param_value_size_ret);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_VALUE:
        printf("Error: Invalid information parameter or insufficient buffer size to store program information.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_PROGRAM:
        printf("Error: Invalid program object parameter.\n");
        exit(EXIT_FAILURE);
    }
}

void releaseProgram(cl_program program)
{
    cl_int result = clReleaseProgram(program);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Program released.\n");
        break;

    case CL_INVALID_PROGRAM:
        printf("Error: Invalid program object.\n");
        exit(EXIT_FAILURE);
    }
}

