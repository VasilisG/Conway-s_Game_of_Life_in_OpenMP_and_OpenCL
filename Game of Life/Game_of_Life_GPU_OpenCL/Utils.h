#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Globals.h"

/* Utility functions */
FILE * initRecordFile(const char *recordFileName);
void readKernelSourceFile(const char *filename, char *kernelSource, size_t *sourceLength);
void linearInitGrid(grid_t grid[SIZE * SIZE]);
void linearFillGrid(grid_t grid[SIZE * SIZE], const char *patternFileName);
void linearRandomFillGrid(grid_t grid[SIZE * SIZE]);
void linearFillGridFromPatternFile(grid_t grid[SIZE * SIZE], const char *filename);
void linearShowGrid(grid_t grid[SIZE * SIZE]);
void showFailureMessage(const char *message);

#endif // UTILS_H
