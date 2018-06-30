#include "Utils.h"

FILE * initRecordFile(const char *recordFileName)
{
    FILE *file;

    if(recordFileName != NULL){
        file = fopen(recordFileName, "w");
        if(file == NULL){
            printf("Could not open file %s\n", recordFileName);
            exit(EXIT_FAILURE);
        }
        else printf("Time calculation file \"%s\" created.\n", recordFileName);
    }
    else{
        printf("You need to define a name for your save file.\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void readKernelSourceFile(const char *filename, char *kernelSource, size_t *sourceLength)
{
    size_t fileSize;
    FILE *file;

    file = fopen(filename, "rb");
    if(file == NULL){
        printf("Error: Could not load kernel source file %s.\n", filename);
        return;
    }

    printf("Opened file...\n");

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    printf("Found file size: %d bytes\n", fileSize);

    kernelSource = (char *)malloc(fileSize);

    printf("Allocated memory...\n");

    if(kernelSource == NULL){
        printf("Error: Could not allocate memory for kernel file contents.\n");
        return;
    }

    if(fread(kernelSource, 1, fileSize, file) != fileSize)
    {
        printf("Closing file...\n");
        fclose(file);
        free(kernelSource);
        return;
    }

    fclose(file);
    *sourceLength = fileSize;
    kernelSource[fileSize] = '\0';

    printf("Kernel source file successfully read.\n");
}

void linearFillGridFromPatternFile(grid_t grid[SIZE * SIZE], const char *filename) {

    FILE *patternFile = fopen(filename, "r");
    if(patternFile == NULL){
        printf("Failed to load file to project file.");
        return;
    }

    char cellChar;
    int row = 400;
    int column = 350;
    while((cellChar = fgetc(patternFile)) != EOF){
        if(cellChar == '\n'){
            row++;
            column = 350;
        }
        else{
            column++;
            if(cellChar=='*'){
                grid[row * SIZE + column] = ALIVE;
            }
            else grid[row * SIZE + column] = DEAD;
        }
    }
}


void linearInitGrid(grid_t grid[SIZE * SIZE])
{
    int pos;
    for(pos=0; pos<SIZE * SIZE; pos++){
        grid[pos] = DEAD;
    }
}

void linearFillGrid(grid_t grid[SIZE * SIZE], const char *patternFileName)
{
    if(patternFileName == NULL){
        linearRandomFillGrid(grid);
    }
    else linearFillGridFromPatternFile(grid, patternFileName);
}

void linearRandomFillGrid(grid_t grid[SIZE * SIZE])
{
    int pos, randomNumber;

    srand(time(NULL));

    for(pos=0; pos<SIZE * SIZE; pos++){
        randomNumber = rand() % 10 + 1;
        if(randomNumber >= 9) grid[pos] = ALIVE;
    }
}

void linearShowGrid(grid_t grid[SIZE * SIZE])
{
    int i,j;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            printf("%5d ", grid[j * SIZE + i]);
        }
        printf("\n");
    }
}

void showFailureMessage(const char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}
