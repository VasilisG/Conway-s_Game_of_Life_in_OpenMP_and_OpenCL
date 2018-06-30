#include "Device.h"

void getDevices(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id *device, cl_uint *num_devices)
{
    cl_int result = clGetDeviceIDs(platform, device_type, num_entries, device, num_devices);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Successfully got devices.\n");
        printf("Number of devices found on platform: %d\n\n", *num_devices);
        break;

    case CL_INVALID_PLATFORM:
        printf("Failed to get devices:\nInvalid platform.\n\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_DEVICE_TYPE:
        printf("Failed to get devices:\nDevice type does not match any known device type constant.\n\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Failed to get devices:\nInvalid parameter values.\n");
        exit(EXIT_FAILURE);

    case CL_DEVICE_NOT_FOUND:
        printf("Failed to get device:\nNo device matches with \"device type\"\n\n");

    case CL_OUT_OF_RESOURCES:
        printf("Failed to get devices:\nInsufficient allocated space.\n\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Failed to get devices:\nCould not allocate resources\n\n");
        exit(EXIT_FAILURE);
    }
}

void getDeviceInfo(cl_device_id device, cl_device_info device_info, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
{
    cl_int result = clGetDeviceInfo(device, device_info, param_value_size, param_value, param_value_size_ret);

    switch(result)
    {
    case CL_SUCCESS:
        //printf("Successfully got device info:\n");
        break;

    case CL_INVALID_DEVICE:
        printf("Failed to get device info:\nInvalid device parameter.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Failed to get device info:\nInsufficient allocated space.\n\n");
        exit(EXIT_FAILURE);

     case CL_OUT_OF_HOST_MEMORY:
        printf("Failed to get devices:\nCould not allocate resources\n\n");
        exit(EXIT_FAILURE);
    }
}

void getAllDeviceInfo(cl_device_id device, size_t param_value_size)
{
    cl_uint max_compute_units;
    cl_uint max_work_item_dimensions;
    size_t max_work_item_sizes[MAX_WORK_ITEM_DIMENSIONS];
    size_t max_work_group_size;

    printf("Device info:\n\n");

    getDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units), &max_compute_units, NULL);
    printf("DEVICE_MAX_COMPUTE_UNITS: %d\n", max_compute_units);
    getDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(max_work_item_dimensions), &max_work_item_dimensions, NULL);
    printf("DEVICE_MAX_WORK_ITEM_DIMENSIONS: %d\n", max_work_item_dimensions);

    getDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(max_work_item_sizes), max_work_item_sizes, NULL);

    cl_uint ui;
    for(ui=0; ui<max_work_item_dimensions; ui++){
        printf("CL_DEVICE_MAX_WORK_ITEM_SIZES[%d]: %d\n", ui, max_work_item_sizes[ui]);
    }

    getDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
    printf("DEVICE_MAX_WORK_GROUP_SIZE: %d\n\n", max_work_group_size);
}

