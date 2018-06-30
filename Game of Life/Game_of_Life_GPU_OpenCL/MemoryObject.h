#ifndef MEMORY_OBJECT_H
#define MEMORY_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <GL/gl.h>

/* Functions that wrap OpenCL memory object functions.*/
cl_mem createBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr);
cl_mem createSubBuffer(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info);
cl_mem createFromGLBuffer(cl_context context, cl_mem_flags flags, GLuint bufobj);
cl_mem createFromGLTexture(cl_context context, cl_mem_flags flags, GLenum texture_target, GLint miplevel, GLuint texture);
void releaseMemObject(cl_mem memObject);

#endif // MEMORY_OBJECT_H
