#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Message title followed by description */
#define ERROR_MESSAGE "[ERROR]: "
#define INFO_MESSAGE  "[INFO]: "

/* Standard OpenCL allocation failure messages */
#define OPENCL_OUT_OF_RESOURCES_MESSAGE     "Failed to allocate resources required by the OpenCL implementation on the device.\n"
#define OPENCL_OUT_OF_HOST_MEMORY           "Failed to allocate resources required by the OpenCL implementation on the host.\n"

/* Platform info and error messages */
#define PLATFORM_RETRIEVAL_SUCCESSFULL      "Retrieving platform info successful.\n\n"
#define PLATFORM_INVALID_VALUE              "Failed to get platform IDs. Please validate [entries > 0] and ([platforms != NULL] or [num_platforms != NULL])\n\n"
#define PLATFORM_INVALID_PLATFORM           "Invalid platform.\n\n"

/* Device info and error messages */
#define DEVICE_RETRIEVAL_SUCCESSFULL        "Successfully got devices.\n\n"
#define DEVICE_INFO_RETRIEVAL_SUCCESSFULL   "Successfully got device info:\n\n"
#define DEVICE_INVALID_DEVICE_TYPE          "Device type does not match any known device type constant.\n\n"
#define DEVICE_INVALID_PARAMETER_VALUE      "Invalid parameter values.\n\n"
#define DEVICE_NOT_FOUND                    "No device matches with \"device type\".\n\n"

/* Context info and error messages */
#define CONTEXT_CREATION_SUCCESSFULL        "Successfully created context.\n\n"
#define CONTEXT_INVALID_PLATFORM            "Context properties cannot be set to NULL.\n\n"
#define CONTEXT_INVALID_VALUE               "Invalid context properties.\n\n"
#define CONTEXT_INVALID_DEVICE              "Invalid device parameter.\n\n"
#define CONTEXT_DEVICE_NOT_AVAILABLE        "Device not available.\n\n"
#define CONTEXT_RELEASED                    "Context released.\n\n"

/* Command queue info and error messages */
#define COMMAND_QUEUE_CREATION_SUCCESSFULL  "Successfully created command queue.\n\n"
#define COMMAND_QUEUE_INVALID_CONTEXT       "Invalid context.\n\n"
#define COMMAND_QUEUE_INVALID_DEVICE        "Invalid device or device not associated with context.\n\n"
#define COMMAND_QUEUE_INVALID_VALUE         "Invalid properties.\n\n"
#define COMMAND_QUEUE_INVALID_PROPERTIES    "Some properties may not be supported by selected device.\n\n"
#define COMMAND_QUEUE_RELEASED              "Command queue released.\n\n"

/* Utility functions info and error messages */
#define UTILITY_ERROR_LOADING_KERNEL        "Could not load kernel source file.\n\n"
#define UTILITY_MEMORY_ALLOCATION_FAILURE   "Could not allocate memory for kernel source file.\n\n"
#define UTILITY_KERNEL_READ_SUCCESSFULL     "Successfully read kernel source file.\n\n"
#define UTILITY_ERROR_LOADING_PATTERN_FILE  "Could not load pattern file.\n\n"

/* Program info and error messages */
#define PROGRAM_CREATION_SUCCESSFULL        "Program successfully created with kernel source.\n\n"
#define PROGRAM_INVALID_CONTEXT             "Invalid context.\n\n"
#define PROGRAM_INVALID_KERNEL_SOURCE       "Invalid kernel source (possibly NULL line in source)\n\n"
#define PROGRAM_RELEASED                    "Program released.\n\n"

#define PROGRAM_BUILD_INFO_INVALID_DEVICE   "Device is not in the list of devices associated with the program.\n\n"
#define PROGRAM_BUILD_INFO_INVALID_VALUE    "Invalid parameter value or insufficient buffer size to store build information.\n\n"
#define PROGRAM_BUILD_INFO_INVALID_PROGRAM  "Invalid program object parameter.\n\n"
#define PROGRAM_BUILD_INFO_LOG              "Program build log:\n\n"

#define PROGRAM_INFO_INVALID_VALUE          "Invalid information parameter or insufficient buffer size to store program information.\n\n"
#define PROGRAM_INFO_INVALID_PROGRAM        "Invalid program object parameter.\n\n"

/* Kernel info and error messages */
#define KERNEL_CREATION_SUCCESSFULL         "Kernel successfully created.\n\n"
#define KERNEL_RELEASED                     "Kernel released.\n\n"
#define KERNEL_INVALID_PROGRAM              "Invalid program object.\n\n"
#define KERNEL_INVALID_PROGRAM_EXECUTABLE   "There is no successfully built executable for program object.\n\n"
#define KERNEL_INVALID_KERNEL_NAME          "Invalid kernel name.\n\n"
#define KERNEL_INVALID_KERNEL_DEFINITION    "Kernel definition is not the same for all devices for which the program executable has been built.\n\n"
#define KERNEL_INVALID_VALUE                "Kernel name is NULL.\n\n"

#define KERNEL_NUMBER_OF_ARGS               "Number of kernel arguments: "
#define KERNEL_ARGUMENT_INVALID_VALUE       "Invalid information parameter or insufficient buffer size to store kernel information.\n\n"
#define KERNEL_ARGUMENT_INVALID_KERNEL      "Kernel is not a valid object.\n\n"
#define KERNEL_ARGUMENT_ADD_ARG_TO_KERNEL   "Added argument to kernel.\n\n"
#define KERNEL_INVALID_ARG_INDEX            "Invalid argument index. (Must fit with the index in kernel's declaration)\n\n"
#define KERNEL_INVALID_ARG_VALUE            "Argument value is NULL.\n\n"
#define KERNEL_INVALID_MEM_OBJECT           "Argument value is not a valid memory object.\n\n"
#define KERNEL_INVALID_SAMPLER              "Argument value is not a valid sampler object.\n\n"
#define KERNEL_INVALID_ARG_SIZE             "Argument size does not match the size of a datatype.\n\n"

/* Memory objects info and error messages */
#define BUFFER_OBJECT_CREATION_SUCCESSFULL  "Buffer object successfully created.\n\n"
#define BUFFER_INVALID_CONTEXT              "Invalid context.\n\n"
#define BUFFER_INVALID_VALUE                "Invalid values in \'flags\' parameter.\n\n"
#define BUFFER_INVALID_BUFFER_SIZE          "Invalid buffer size. (Must be greater than 0)\n\n"
#define BUFFER_INVALID_HOST_PTR             "Invalid \'host_ptr\' parameter.\n\n"
#define BUFFER_MEM_OBJ_ALLOCATION_FAILURE   "Failed to allocate memory for buffer object.\n\n"
#define BUFFER_OBJECT_RELEASED              "Released buffer object.\n\n"

#define GL_BUFFER_CREATION_SUCCESSFULL      "Buffer object successfully created from GL buffer.\n\n"
#define GL_BUFFER_INVALID_CONTEXT           "Invalid context.\n\n"
#define GL_BUFFER_INVALID_VALUE             "Invalid flag values.\n\n"
#define GL_BUFFER_INVALID_GL_OBJECT         "GL buffer object is not a valid object or GL buffer object does not have an existing data store.\n\n"

#define GL_TEXTURE_CREATION_SUCCESSFULL                 "Buffer object successfully created from GL texture.\n\n"
#define GL_TEXTURE_INVALID_MIP_LEVEL                    "Invalid \'miplevel\' parameter.\n\n"
#define GL_TEXTURE_INVALID_GL_OBJECT                    "OpenGL texture internal format does not map to a supported OpenCL image format.\n\n"
#define GL_TEXTURE_INVALID_IMAGE_FORMAT_DESCRIPTOR      "OpenGL texture internal format does not map to a supported OpenCL image format.\n\n"
#define GL_TEXTURE_INVALID_OPERATION                    "Invalid operation. ( GL texture object created with a border width value greater than zero)\n\n"

/* Enqueue info and error messages */
#define ENQUEUE_READ_BUFFER_SUCCESSFULL      "Successfully read buffer.\n\n"
#define ENQUEUE_WRITE_BUFFER_SUCCESSFULL     "Successfully wrote buffer.\n\n"

#define ENQUEUE_INVALID_COMMAND_QUEUE        "Invalid command queue parameter.\n\n"
#define ENQUEUE_INVALID_CONTEXT              "Invalid context parameter. (Context associated with \'command_queue\' and \'buffer\' are not the same or context associated with \'command_queue\' and \'event_wait_list\' are not the same.\n"

#define ENQUEUE_INVALID_MEM_OBJECT           "\'buffer\' parameter is not a valid buffer object.\n\n"
#define ENQUEUE_INVALID_VALUE                "Invalid \'offset\' and \'size\' values (out of bounds) or \'ptr\' is NULL or \'size\' is 0.\n\n"
#define ENQUEUE_INVALID_EVENT_WAIT_LIST      "Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n\n"

#define ENQUEUE_MISALIGNED_SUB_BUFFER_OFFSET "Misaligned sub-buffer object. (Sub-buffer object's offset is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue)\n\n"
#define ENQUEUE_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST   "Execution status error. (Read operation is set to \'blocking\' and any of the events in \'event_wait_list\' is a negative number.\n\n"
#define ENQUEUE_MEM_OBJECT_ALLOCATION_FAILURE               "Failed to allocate memory for data store associated with \'buffer\'.\n\n"
#define ENQUEUE_INVALID_READ_OPERATION                      "Function called on buffer which has been created with CL_MEM_HOST_WRITE_ONLY or CL_MEM_HOST_NO_ACCESS.\n\n"
#define ENQUEUE_INVALID_WRITE_OPERATION                     "Function called on buffer which has been created with CL_MEM_HOST_READ_ONLY or CL_MEM_HOST_NO_ACCESS.\n\n"

#define ENQUEUE_COPY_BUFFER_SUCCESSFULL     "Successfully copied buffer.\n\n"
#define ENQUEUE_COPY_INVALID_COMMAND_QUEUE  "Invalid command queue.\n\n"
#define ENQUEUE_COPY_INVALID_CONTEXT        "Invalid context.\n\n"
#define ENQUEUE_COPY_INVALID_MEM_OBJECT     "\'src_buffer\' or \'dst_buffer\' are not valid buffer objects.\n\n"
#define ENQUEUE_COPY_INVALID_VALUE          "\'size\' must be greater than 0.\n\n"
#define ENQUEUE_COPY_INVALID_EVENT_WAIT_LIST    "Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n\n"

#define ENQUEUE_COPY_MISALIGNED_SUB_BUFFER_OFFSET   "Misaligned sub-buffer object. (\'src_buffer\' or \'dst_buffer\' object's offset is not aligned to CL_DEVICE_MEM_BASE_ADDR_ALIGN value for device associated with queue)\n\n"

#define ENQUEUE_COPY_MEM_COPY_OVERLAP               "\'src_buffer\' and \'dst_buffer\' overlap with each other. (Either point to the same buffer or their offsets' ranges intersect)\n\n"
#define ENQUEUE_COPY_MEM_OBJECT_ALLOCATION_FAILURE  "Failed to allocate memory for data store associated with either \'src_buffer\' or \'dst_buffer\'.\n\n"


#define ENQUEUE_NDRANGE_INVALID_PROGRAM_EXECUTABLE  "There is no successfully built program executable for device associated with \'command_queue\' parameter.\n\n"
#define ENQUEUE_NDRANGE_INVALID_COMMAND_QUEUE       "Invalid \'command_queue\' parameter.\n\n"
#define ENQUEUE_NDRANGE_INVALID_KERNEL              "Invalid \'kernel\' object parameter.\n\n"
#define ENQUEUE_NDRANGE_INVALID_CONTEXT             "Context associated with \'command_queue\' and \'kernel\' or \'event_wait_list\' is not the same.\n\n"
#define ENQUEUE_NDRANGE_INVALID_KERNEL_ARGS         "Kernel arguments have not been specified.\n\n"
#define ENQUEUE_NDRANGE_INVALID_WORK_DIMENSION      "Invalid \'work_dim\' value. (Must be in range : [1,3])\n\n"
#define ENQUEUE_NDRANGE_INVALID_WORK_GROUP_SIZE     "Invalid work group size. (Number of work items specified by \'global_work_size\' are not evenly divisible by size of work group given by \'local_work_size\' or do not match with kernel argument)\n\n"

#define ENQUEUE_NDRANGE_INVALID_WORK_ITEM_SIZE          "Invalid \'local_work_size\'. (Must be less or equal to CL_DEVICE_MAX_WORK_ITEM_SIZES[..])\n\n"
#define ENQUEUE_NDRANGE_INVALID_GLOBAL_OFFSET           "Invalid \'global_work_offset\' parameter.\n\n"
#define ENQUEUE_NDRANGE_MEM_OBJECT_ALLOCATION_FAILURE   "Failed to allocate memory for data store associated with image or buffer objects specified as arguments to \'kernel\'.\n\n"
#define ENQUEUE_NDRANGE_INVALID_EVENT_WAIT_LIST         "Invalid \'event_wait_list\' or \'num_events_in_wait_list\' parameters. (Either \'event_wait_list\' is NULL or \'num_events_in_wait_list\' is 0 or both are invalid objects.\n\n"

#define ENQUEUE_GL_OBJECT_INVALID_VALUE                   "Invalid values of \'num_objects\' and \'mem_objects\'.\n\n"
#define ENQUEUE_GL_OBJECT_INVALID_CONTEXT                 "Context associated with \'command_queue\' was not created from an OpenGL context.\n\n"
#define ENQUEUE_GL_OBJECT_INVALID_GL_OBJECT               "Memory object was not created from a GL object.\n\n"

#endif // CONSTANTS_H
