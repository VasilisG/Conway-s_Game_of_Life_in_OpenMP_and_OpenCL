#ifndef PROFILE_H
#define PROFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

void waitForEvents(cl_uint num_events, const cl_event *event_list);
void getEventProfilingInfo(cl_event event, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);

#endif // PROFILE_H
