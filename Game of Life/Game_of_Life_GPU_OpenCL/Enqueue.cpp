#include "Enqueue.h"

void enqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
    cl_int result = clEnqueueReadBuffer(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);

    switch(result)
    {
    case CL_SUCCESS:
        //printf("Successfully read buffer.\n");
        break;

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context parameter. (Context associated with \'command_queue\' and \'buffer\' are not the same or context associated with \'command_queue\' and \'event_wait_list\' are not the same.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MEM_OBJECT:
        printf("Error: \'buffer\' parameter is not a valid buffer object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid \'offset\' and \'size\' values (out of bounds) or \'ptr\' is NULL or \'size\' is 0.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT_WAIT_LIST:
        printf("Error: Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n");
        exit(EXIT_FAILURE);

    case CL_MISALIGNED_SUB_BUFFER_OFFSET:
        printf("Error: Misaligned sub-buffer object. (Sub-buffer object's offset is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue)\n");
        exit(EXIT_FAILURE);

    case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
        printf("Error: Execution status error. (Read operation is set to \'blocking\' and any of the events in \'event_wait_list\' is a negative number.\n");
        exit(EXIT_FAILURE);

    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        printf("Error: Failed to allocate memory for data store associated with \'buffer\'.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_OPERATION:
        printf("Error: Function called on buffer which has been created with CL_MEM_HOST_WRITE_ONLY or CL_MEM_HOST_NO_ACCESS.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void enqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
    cl_int result = clEnqueueWriteBuffer(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);

    switch(result)
    {
    case CL_SUCCESS:
        //printf("Successfully wrote buffer.\n");
        break;

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context parameter. (Context associated with \'command_queue\' and \'buffer\' are not the same or context associated with \'command_queue\' and \'event_wait_list\' are not the same.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MEM_OBJECT:
        printf("Error: \'buffer\' parameter is not a valid buffer object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid \'offset\' and \'size\' values (out of bounds) or \'ptr\' is NULL or \'size\' is 0.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT_WAIT_LIST:
        printf("Error: Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n");
        exit(EXIT_FAILURE);

    case CL_MISALIGNED_SUB_BUFFER_OFFSET:
        printf("Error: Misaligned sub-buffer object. (Sub-buffer object's offset is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue)\n");
        exit(EXIT_FAILURE);

    case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
        printf("Error: Execution status error. (Read operation is set to \'blocking\' and any of the events in \'event_wait_list\' is a negative number.\n");
        exit(EXIT_FAILURE);

    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        printf("Error: Failed to allocate memory for data store associated with \'buffer\'.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_OPERATION:
        printf("Error: Function called on buffer which has been created with CL_MEM_HOST_READ_ONLY or CL_MEM_HOST_NO_ACCESS.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void enqueueCopyBuffer(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
    cl_int result = clEnqueueCopyBuffer(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event);

    switch(result)
    {
    case CL_SUCCESS:
        //printf("Successfully copied buffer.\n");
        break;

     case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context parameter. (Context associated with \'command_queue\', \'src_buffer\' and \'dst_buffer\' is not the same or context associated with \'command_queue\' and \'event_wait_list\' is not the same.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MEM_OBJECT:
        printf("Error: \'src_buffer\' or \'dst_buffer\' are not valid buffer objects.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: \'size\' must be greater than 0.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT_WAIT_LIST:
        printf("Error: Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n");
        exit(EXIT_FAILURE);

    case CL_MISALIGNED_SUB_BUFFER_OFFSET:
        printf("Error: Misaligned sub-buffer object. (\'src_buffer\' or \'dst_buffer\' object's offset is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue)\n");
        exit(EXIT_FAILURE);

    case CL_MEM_COPY_OVERLAP:
        printf("Error: \'src_buffer\' and \'dst_buffer\' overlap with each other. (Either point to the same buffer or their offsets' ranges intersect)\n");
        exit(EXIT_FAILURE);

    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        printf("Error: Failed to allocate memory for data store associated with either \'src_buffer\' or \'dst_buffer\'.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void enqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, 	cl_uint num_events_in_wait_list,
                          const cl_event *event_wait_list,
                          cl_event *event)
{
    cl_int result = clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_PROGRAM_EXECUTABLE:
        printf("Error: There is no successfully built program executable for device associated with \'command_queue\' parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid \'command_queue\' parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_KERNEL:
        printf("Error: Invalid \'kernel\' object parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Context associated with \'command_queue\' and \'kernel\' or \'event_wait_list\' is not the same.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_KERNEL_ARGS:
        printf("Error: Kernel arguments have not been specified.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_WORK_DIMENSION:
        printf("Error: Invalid \'work_dim\' value. (Must be in range : [1,3])\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_WORK_GROUP_SIZE:
        printf("Error: Invalid work group size. (Number of work items specified by \'global_work_size\' are not evenly divisible by size of work group given by \'local_work_size\' or do not match with kernel argument)\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_WORK_ITEM_SIZE:
        printf("Error: Invalid \'local_work_size\'. (Must be less or equal to CL_DEVICE_MAX_WORK_ITEM_SIZES[..])\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_GLOBAL_OFFSET:
        printf("Error: Invalid \'global_work_offset\' parameter.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Insufficient resources needed to execute kernel.\n");
        exit(EXIT_FAILURE);

    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        printf("Error: Failed to allocate memory for data store associated with image or buffer objects specified as arguments to \'kernel\'.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT_WAIT_LIST:
        printf("Error: Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources for the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}

void enqueueAcquireGLObjects(cl_command_queue command_queue, cl_uint num_objects, const cl_mem * mem_objects, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
    cl_int result = clEnqueueAcquireGLObjects(command_queue, num_objects, mem_objects, num_events_in_wait_list, event_wait_list, event);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_VALUE:
        printf("Error: Invalid values of \'num_objects\' and \'mem_objects\'.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MEM_OBJECT:
        printf("Error: Invalid memory object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Context associated with \'command_queue\' was not created from an OpenGL context.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_GL_OBJECT:
        printf("Error: Memory object was not created from a GL object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT_WAIT_LIST:
        printf("Error: Invalid event wait list.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required from the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);

    }
}

void enqueueReleaseGLObjects(cl_command_queue command_queue, cl_uint num_objects, const cl_mem *mem_objects, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
    cl_int result = clEnqueueReleaseGLObjects(command_queue, num_objects, mem_objects, num_events_in_wait_list, event_wait_list, event);

    switch(result)
    {
    case CL_SUCCESS:
        break;

    case CL_INVALID_VALUE:
        printf("Error: Invalid values of \'num_objects\' and \'mem_objects\'.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MEM_OBJECT:
        printf("Error: Memory object was not created from a GL object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_COMMAND_QUEUE:
        printf("Error: Invalid command queue.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_GL_OBJECT:
        printf("Error: Memory object was not created from a GL object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_EVENT_WAIT_LIST:
        printf("Error: Invalid \'event_wait_list\'.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required from the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
}
