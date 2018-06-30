#ifndef GLOBALS_H
#define GLOBALS_H

#define WINDOW_TITLE "Game of life - GPU implementation / OpenCL"

#define SIZE 1024

#define SCREEN_SIZE 1024

#define POINT_SIZE 1

#define ALIVE 1
#define DEAD 0

/* Platform constants. */
#define PLATFORM_ENTRIES 4
#define PLATFORM_ATTRIBUTES 5

/* Not to be confused with buffer objects. They are sizes of strings retrieving and returning information. */
#define INFO_BUFFER 1024
#define SOURCE_BUFFER 1024
#define KERNEL_BUFFER 1024

/* Size for strings to be displayed in window. */
#define INFO_SIZE 100

/* Size of filename strings. */
#define FILENAME_SIZE 30
#define STRING_SIZE 10

/* Number of device entries to get from OpenCL. */
#define DEVICE_ENTRIES 4

/* GPU specifications. */
#define MAX_WORK_ITEM_DIMENSIONS 3
#define WORK_GROUP_SIZE 256

/* Maximum number of iterations in which update time will be recorded and written to file. */
#define ITERATIONS 1000

/* Giving an alias to the type of data that grid will host. */
typedef int grid_t;

/* Alias for unsigned int data type. */
typedef unsigned int uint;

#endif // GLOBALS_H
