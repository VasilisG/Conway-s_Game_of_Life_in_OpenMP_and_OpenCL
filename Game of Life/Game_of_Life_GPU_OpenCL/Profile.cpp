#include "Profile.h"

void waitForEvents(cl_uint num_events, const cl_event *event_list)
{
    cl_int result = clWaitForEvents(num_events, event_list);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_VALUE:
        printf("Error: Invalid values ('num_events'==0 or 'event_list'==NULL)\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Events specified in 'event_list' do not belong in current context.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT:
        printf("Error: Invalid event objects.\n");
        exit(EXIT_FAILURE);

    case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
        printf("Error: Execution status of event in event list is negative number.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Could not allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Could not allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void getEventProfilingInfo(cl_event event, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
{
    cl_int result = clGetEventProfilingInfo(event, param_name, param_value_size, param_value, param_value_size_ret);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_PROFILING_INFO_NOT_AVAILABLE:
        printf("Error: Profiling info currently unavailable (CL_QUEUE_PROFILING_ENABLE flag not set in command queue).\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid parameter values.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT:
        printf("Error: Invalid event object.\n");
        exit(EXIT_FAILURE);
    }
}
