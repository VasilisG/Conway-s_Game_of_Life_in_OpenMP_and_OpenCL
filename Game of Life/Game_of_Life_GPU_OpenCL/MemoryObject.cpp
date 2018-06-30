#include "MemoryObject.h"

cl_mem createBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr)
{
    cl_int result;
    cl_mem buffer = clCreateBuffer(context, flags, size, host_ptr, &result);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Buffer object successfully created.\n");
        break;

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid values in \'flags\' parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_BUFFER_SIZE:
        printf("Error: Invalid buffer size. (Must be greater than 0)\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_HOST_PTR:
        printf("Error: Invalid \'host_ptr\' parameter.\n");
        exit(EXIT_FAILURE);

    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        printf("Error: Failed to allocate memory for buffer object.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCl implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

cl_mem createSubBuffer(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info)
{
    cl_int result;
    cl_mem subBuffer = clCreateSubBuffer(buffer, flags, buffer_create_type, buffer_create_info, &result);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Sub-buffer object successfully created.\n");
        break;

    case CL_INVALID_MEM_OBJECT:
        printf("Error: Invalid \'buffer\' object parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Parameter mismatch between \'buffer\' and \'flags\' or invalid \'buffer_create_type\' or \'buffer_create_info\' parameters.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_BUFFER_SIZE:
        printf("Error: Invalid buffer size. (Must be greater than 0)\n");
        exit(EXIT_FAILURE);

    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        printf("Error: Failed to allocate memory for sub-buffer object.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCl implementation on the host.\n");
        exit(EXIT_FAILURE);
    }
    return subBuffer;
}

cl_mem createFromGLBuffer(cl_context context, cl_mem_flags flags, GLuint bufobj)
{
    cl_int result;

    cl_mem glBuffer = clCreateFromGLBuffer(context, flags, bufobj, &result);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Buffer object successfully created from GL buffer.\n");
        break;

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid flag values.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_GL_OBJECT:
        printf("Error: GL buffer object is not a valid object or GL buffer object does not have an existing data store.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }

    return glBuffer;
}

cl_mem createFromGLTexture(cl_context context, cl_mem_flags flags, GLenum texture_target, GLint miplevel, GLuint texture)
{
    cl_int result;

    cl_mem glTextureBuffer = clCreateFromGLTexture(context, flags, texture_target, miplevel, texture, &result);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Buffer object successfully created from GL texture.\n");
        break;

    case CL_INVALID_CONTEXT:
        printf("Error: Invalid context parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_VALUE:
        printf("Error: Invalid flag values.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_MIP_LEVEL:
        printf("Error: Invalid \'miplevel\' parameter.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_GL_OBJECT:
        printf("Error: Invalid GL object.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
        printf("Error: OpenGL texture internal format does not map to a supported OpenCL image format.\n");
        exit(EXIT_FAILURE);

    case CL_INVALID_OPERATION:
        printf("Error: Invalid operation ( GL texture object created with a border width value greater than zero).\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_RESOURCES:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the device.\n");
        exit(EXIT_FAILURE);

    case CL_OUT_OF_HOST_MEMORY:
        printf("Error: Failed to allocate resources required by the OpenCL implementation on the host.\n");
        exit(EXIT_FAILURE);
    }

    return glTextureBuffer;
}

void releaseMemObject(cl_mem memObject)
{
    cl_int result = clReleaseMemObject(memObject);

    switch(result)
    {
    case CL_SUCCESS:
        printf("Memory object released.\n");
        break;

    case CL_INVALID_MEM_OBJECT:
        printf("Error: Invalid memory object.\n");
        exit(EXIT_FAILURE);
    }
}
