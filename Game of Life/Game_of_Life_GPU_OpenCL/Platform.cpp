#include "Platform.h"

void getPlatforms(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms)
{
    cl_int result = clGetPlatformIDs(num_entries, platforms, num_platforms);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_VALUE:
        printf("Failed to get platform IDs. Please validate [entries > 0] and ([platforms != NULL] or [num_platforms != NULL])\n\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Failed to get platform IDs. Resource allocation failed.\n\n");
        exit(EXIT_FAILURE);

    }
}

void initPlatformAttributes(cl_platform_info attributes[PLATFORM_ATTRIBUTES])
{
    attributes[0] = CL_PLATFORM_NAME;
    attributes[1] = CL_PLATFORM_VENDOR;
    attributes[2] = CL_PLATFORM_VERSION;
    attributes[3] = CL_PLATFORM_PROFILE;
    attributes[4] = CL_PLATFORM_EXTENSIONS;
}

void showPlatformAttributes(cl_platform_info attributes[PLATFORM_ATTRIBUTES])
{
    int i;
    for(i=0; i<PLATFORM_ATTRIBUTES; i++){
        printf("Attribute %d: %d\n", i, attributes[i]);
    }
}

void getPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, char *param_value, size_t *param_value_size_ret)
{
    cl_int result;
    result = clGetPlatformInfo(platform, param_name, param_value_size, param_value, param_value_size_ret);

    switch(result)
    {
    case CL_SUCCESS:
        printf("%s\n", param_value);
        break;

    case CL_INVALID_PLATFORM:
        printf("\nFailed to get platform information. Invalid platform.\n\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("\nFailed to get platform information on \"param_name\". Invalid platform attribute.\n\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("\nFailed to get platform information. Resource allocation failed.\n\n");
        exit(EXIT_FAILURE);
    }
}

void getAllPlatformInfo(cl_uint num_platforms, cl_platform_id *platforms, size_t param_value_size, char *param_value, size_t *param_value_size_ret)
{
    cl_uint ui;
    for(ui=0; ui<num_platforms; ui++){

        printf("Platform name: ");
        getPlatformInfo(platforms[ui], CL_PLATFORM_NAME, param_value_size, param_value, param_value_size_ret);
        printf("Platform vendor: ");
        getPlatformInfo(platforms[ui], CL_PLATFORM_VENDOR, param_value_size, param_value, param_value_size_ret);
        printf("Platform version: ");
        getPlatformInfo(platforms[ui], CL_PLATFORM_VERSION, param_value_size, param_value, param_value_size_ret);
        printf("Platform profile: ");
        getPlatformInfo(platforms[ui], CL_PLATFORM_PROFILE, param_value_size, param_value, param_value_size_ret);
        printf("Platform extensions: ");
        getPlatformInfo(platforms[ui], CL_PLATFORM_EXTENSIONS, param_value_size, param_value, param_value_size_ret);
        printf("\n");
    }

}
