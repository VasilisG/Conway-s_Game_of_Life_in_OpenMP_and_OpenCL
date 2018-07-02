# Game of Life in OpenMP and OpenCL

The above projects are implementations of Conway's Game of Life for OpenMP, OpenMP 4.0 (SIMD) and OpenCL.

## Game of Life

The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties.

### Game's rules

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

 *   Any live cell with fewer than two live neighbors dies, as if by under population.
 *   Any live cell with two or three live neighbors lives on to the next generation.
 *   Any live cell with more than three live neighbors dies, as if by overpopulation.
 *   Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.

For more information, see [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## OpenMP

OpenMP (Open Multi-Processing) is an application programming interface (API) that supports multi-platform shared memory multiprocessing programming in C, C++, and Fortran, on most platforms, instruction set architectures and operating systems, including Solaris, AIX, HP-UX, Linux, macOS, and Windows. It consists of a set of compiler directives, library routines, and environment variables that influence run-time behavior.

### Design

OpenMP is an implementation of multithreading, a method of parallelizing whereby a master thread (a series of instructions executed consecutively) forks a specified number of slave threads and the system divides a task among them. The threads then run concurrently, with the runtime environment allocating threads to different processors.

The section of code that is meant to run in parallel is marked accordingly, with a compiler directive that will cause the threads to form before the section is executed. Each thread has an id attached to it which can be obtained using a function (called omp_get_thread_num()). The thread id is an integer, and the master thread has an id of 0. After the execution of the parallelized code, the threads join back into the master thread, which continues onward to the end of the program.

![alt text](https://github.com/VasilisG/Game-of-Life-in-OpenMP-and-OpenCL/blob/master/Images/OpenMP.png)

By default, each thread executes the parallelized section of code independently. Work-sharing constructs can be used to divide a task among the threads so that each thread executes its allocated part of the code. Both task parallelism and data parallelism can be achieved using OpenMP in this way.

The runtime environment allocates threads to processors depending on usage, machine load and other factors. The runtime environment can assign the number of threads based on environment variables, or the code can do so using functions. The OpenMP functions are included in a header file labelled omp.h in C/C++.

For more information, see [OpenMP](https://www.openmp.org/).

## OpenCL

OpenCL (Open Computing Language) is a framework for writing programs that execute across heterogeneous platforms consisting of central processing units (CPUs), graphics processing units (GPUs), digital signal processors (DSPs), field-programmable gate arrays (FPGAs) and other processors or hardware accelerators. OpenCL specifies programming languages (based on C99 and C++11) for programming these devices and application programming interfaces (APIs) to control the platform and execute programs on the compute devices. OpenCL provides a standard interface for parallel computing using task- and data-based parallelism.

### Overview

OpenCL views a computing system as consisting of a number of compute devices, which might be central processing units (CPUs) or "accelerators" such as graphics processing units (GPUs), attached to a host processor (a CPU). It defines a C-like language for writing programs. Functions executed on an OpenCL device are called "kernels". A single compute device typically consists of several compute units, which in turn comprise multiple processing elements (PEs). A single kernel execution can run on all or many of the PEs in parallel. How a compute device is subdivided into compute units and PEs is up to the vendor; a compute unit can be thought of as a "core", but the notion of core is hard to define across all the types of devices supported by OpenCL (or even within the category of "CPUs"), and the number of compute units may not correspond to the number of cores claimed in vendors' marketing literature (which may actually be counting SIMD lanes).

In addition to its C-like programming language, OpenCL defines an application programming interface (API) that allows programs running on the host to launch kernels on the compute devices and manage device memory, which is (at least conceptually) separate from host memory. Programs in the OpenCL language are intended to be compiled at run-time, so that OpenCL-using applications are portable between implementations for various host devices. The OpenCL standard defines host APIs for C and C++; third-party APIs exist for other programming languages and platforms such as Python, Java and .NET. An implementation of the OpenCL standard consists of a library that implements the API for C and C++, and an OpenCL C compiler for the compute device(s) targeted.

For more information, see [OpenCL](https://www.khronos.org/opencl/).

## Tests

Our system constitutes of the following processing units:

* Intel core i5 4590
* AMD ASUS R9 270X

Tests were run for the following implementations:

* Serial implementation in CPU
* Parallel implementation in CPU using OpenMP for 2,4,8,16,32 threads
* Parallel implementation in CPU using OpenMP 4.0 SIMD
* GPU implementation using OpenCL

and for the following grid sizes:

* 128x128
* 256x256
* 512x512
* 1024x1024

For each grid size, we executed each implementation 10 times for 1000 game iterations and we calculated 10 averages for each time. From these 10 averages we calculated the final average for every implementation in each grid size.

The following diagrams show the update time of each implementation and speedups in relation with the serial implementation respectively:

![alt text](https://github.com/VasilisG/Game-of-Life-in-OpenMP-and-OpenCL/blob/master/Images/times.png)

![alt text](https://github.com/VasilisG/Game-of-Life-in-OpenMP-and-OpenCL/blob/master/Images/speedups.png)

## OpenGL

For data representation, OpenGL was used. The following is a screenshot in a 1024x1024 grid:

![alt text](https://github.com/VasilisG/Game-of-Life-in-OpenMP-and-OpenCL/blob/master/Images/gol_screenshot.png)

## Built with

The following tools/libraries were used to implement Game of Life:

* [Codeblocks](http://www.codeblocks.org/) -  C, C++ and Fortran IDE
* [GLUT](https://www.opengl.org/resources/libraries/glut/) - An API for OpenGL 


## Deployment

Below are instructions on how to build and run each program:

* Game_of_Life_Serial_CPU

```
gcc main.cpp –o main -lGL -lGLU –lglut 
./main
```

* Game_of_Life_Parallel_CPU

```
gcc main.cpp –o main -fopenmp -lGL -lGLU –lglut 
./main
```

* Game_of_Life_Parallel_CPU_OpenMP_4.0 

```
gcc main.cpp –o main -fopenmp -lGL -lGLU –lglut 
./main 
```

* Game_of_Life_GPU_OpenCL

```
gcc main.cpp –o main –lGL –lGLU –lglut –lOpenCL 
./main 
```

## System requirements

* OpenGL 4.2 or higher
* OpenCL 1.2 or higher
* GNU GCC 5.1.0 or higher

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/VasilisG/Game-of-Life-in-OpenMP-and-OpenCL/blob/master/LICENSE) file for details.
