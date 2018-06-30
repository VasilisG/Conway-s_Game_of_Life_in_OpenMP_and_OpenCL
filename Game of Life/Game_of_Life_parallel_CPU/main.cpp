#ifdef _WIN32
    #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <omp.h>

#include "Patterns.h"

#define WINDOW_TITLE "Game of Life - Parallel CPU implementation"

#define RED 0.0
#define GREEN 0.0
#define BLUE 0.0

#define SIZE 1024

#define SCREEN_SIZE 1024

#define POINT_SIZE 1

#define ALIVE 1
#define DEAD 0

#define NUMBER_OF_THREADS 4

#define ITERATIONS 1000

#define INFO_SIZE 100
#define FILENAME_SIZE 30
#define STRING_SIZE 10

//Giving an alias to the type of data that grid will host.
typedef bool grid_t;

//The grid the will host the game.
grid_t grid[SIZE * SIZE];
grid_t tempGrid[SIZE * SIZE];
int aliveCells;
int generation;

//Flag variable.
bool canRender = false;
bool canShowInfo = true;

//File to save time results.
bool benchmarkEnabled = false;
bool isFileClosed = false;
bool fileFirstOpened = false;
int benchmarkGeneration;
int numOfBenchmarkFiles;
char saveFileName[FILENAME_SIZE] = "benchmarkTestFile";
FILE *saveFile;

//Pattern file names from Patterns.h header file.
const char *patternFileName = NULL;

//Variables used for calculating time.
clock_t before, after;
double diff;

//Function that initializes the game's variables.
void initGameVariables();
FILE * openBenchmarkFile(const char * filename);

//Function declarations that deal with the game's grid.
void linearInitGrid(grid_t grid[SIZE * SIZE]);
void linearFillGrid(grid_t grid[SIZE * SIZE], const char *patternFileName);
void linearRandomFillGrid(grid_t grid[SIZE * SIZE]);
void linearFillGridFromPatternFile(grid_t grid[SIZE * SIZE], const char *filename);
void linearUpdateGrid(grid_t grid[SIZE * SIZE]);
int linearGetAliveNeighbors(grid_t grid[SIZE * SIZE], int pos);

//Function declarations that deal with OpenGL.
void displayText(GLint x, GLint y, char *text);
void displayInfo(GLint x, GLint y);
void display(void);
void idle(void);
void changeInfoView(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
    initGameVariables();

    linearInitGrid(grid);
    linearFillGrid(grid, NULL);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(fmin(SIZE, SCREEN_SIZE),fmin(SIZE, SCREEN_SIZE));
    glutCreateWindow(WINDOW_TITLE);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(changeInfoView);
    glutMainLoop();

    return 0;
}

//Function that initializes game variables.
void initGameVariables()
{
    aliveCells = 0;
    generation = 0;
    benchmarkGeneration = 0;
    numOfBenchmarkFiles = 1;
}

//Function that creates the benchmark file object.
FILE * openBenchmarkFile(const char *filename)
{
    FILE *file;

    if(filename != NULL){
        file = fopen(filename, "w");
        if(file == NULL){
            printf("Error: Could not open file %s.\n", filename);
            exit(EXIT_FAILURE);
        }
        else printf("Time calculation file \"%s\" created.\n", filename);
    }
    else {
        printf("Error: You need to define a name for your save file.\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

//Function definitions that deal with the game's grid.
void linearInitGrid(grid_t grid[SIZE * SIZE])
{
    int i;
    #pragma omp parallel for num_threads(NUMBER_OF_THREADS) private(i) shared(grid)
    for(i=0; i<SIZE * SIZE; i++){
        grid[i] = DEAD;
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
     int i, randomNumber;

     srand(time(NULL));

     for(i=0; i<SIZE * SIZE; i++){
        randomNumber = rand() % 10 + 1;
        if(randomNumber >= 9){
            grid[i] = ALIVE;
            aliveCells++;
        }
     }
}

void linearUpdateGrid(grid_t grid[SIZE * SIZE])
{
    int i, aliveNeighbors;

    linearInitGrid(tempGrid);

    before = clock();

    #pragma omp parallel for num_threads(NUMBER_OF_THREADS) private(i, aliveNeighbors) shared(tempGrid, grid)
    for(i=0; i<SIZE * SIZE; i++){
        aliveNeighbors = linearGetAliveNeighbors(grid, i);
        if(grid[i]==ALIVE){
            if(aliveNeighbors==2 || aliveNeighbors==3){
                tempGrid[i] = ALIVE;
            }
            else{
                tempGrid[i] = DEAD;
            }
        }
        else{
            if(aliveNeighbors==3){
                tempGrid[i] = ALIVE;
            }
        }
    }

    memcpy(grid, tempGrid, SIZE * SIZE);

    after = clock();

    diff = (after - before) * 1000.0 / CLOCKS_PER_SEC;

    if(benchmarkEnabled){
        if(!fileFirstOpened){
            char numOfBenchmarkFilesString[STRING_SIZE];
            itoa(numOfBenchmarkFiles, numOfBenchmarkFilesString, 10);
            strcat(saveFileName, numOfBenchmarkFilesString);
            saveFile = openBenchmarkFile(saveFileName);
            memset(saveFileName,0,sizeof(saveFileName));
            strcpy(saveFileName, "benchmarkTestFile");
            fileFirstOpened = true;
            numOfBenchmarkFiles++;
        }

        if(benchmarkGeneration <= ITERATIONS-1){
            fprintf(saveFile,"%f\n",diff);
            benchmarkGeneration++;
        }

        else{
            if(!isFileClosed){
                fclose(saveFile);
                isFileClosed = true;
            }
            fileFirstOpened = false;
            benchmarkGeneration = 0;
            benchmarkEnabled = false;
        }
    }
    else{
        fileFirstOpened = false;
        benchmarkGeneration = 0;
    }
    generation++;
}

int linearGetAliveNeighbors(grid_t grid[SIZE * SIZE], int pos)
{
    int aliveNeighbors = 0;
    int rowUp, rowDown;
    rowUp = pos - SIZE;
    rowDown = pos + SIZE;

    bool outOfBounds = (pos < SIZE);
         outOfBounds |= (pos > (SIZE * (SIZE-1)));
         outOfBounds |= (pos % SIZE == 0);
         outOfBounds |= (pos % SIZE == SIZE-1);

    if(outOfBounds) return 0;

    aliveNeighbors += grid[rowUp-1] + grid[rowUp] + grid[rowUp+1];
    aliveNeighbors += grid[pos-1] + grid[pos+1];
    aliveNeighbors += grid[rowDown-1] + grid[rowDown] + grid[rowDown+1];

    return aliveNeighbors;
}

void linearFillGridFromPatternFile(grid_t grid[SIZE * SIZE], const char *filename) {

    FILE *patternFile = fopen(filename, "r");
    if(patternFile == NULL){
        printf("Failed to load file to project file.");
        return;
    }

    char cellChar;
    int row = 200;
    int column = 150;
    while((cellChar = fgetc(patternFile)) != EOF){
        if(cellChar == '\n'){
            row++;
            column = 150;
        }
        else{
            column++;
            if(cellChar=='*'){
                grid[row * SIZE + column] = ALIVE;
                aliveCells++;
            }
            else grid[row * SIZE + column] = DEAD;
        }
    }
}

// Function definitions that deal with OpenGL.

void changeInfoView(unsigned char key, int x, int y)
{
    if(key == 'v' || key =='V'){
        canShowInfo = !canShowInfo;
    }

    if(key == 'b' || key == 'B'){
        benchmarkEnabled = !benchmarkEnabled;
    }
}

void idle(void){

    linearUpdateGrid(grid);
    canRender = true;

    if(canRender) glutPostRedisplay();
}

void display(void) {

    GLint pos, row, column;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    GLfloat windowWidth = fmin(SIZE, SCREEN_SIZE) * 1.0;
    GLfloat windowHeight = fmin(SIZE, SCREEN_SIZE) * 1.0;

    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    glPointSize(POINT_SIZE);

    glBegin(GL_POINTS);
    for(pos=0; pos < SIZE * SIZE; pos++){
        row = pos % SIZE;
        column = pos / SIZE;
        if(grid[pos]==ALIVE){
            aliveCells++;
            glColor3f(0.0, 0.6, 0.0);
        }
        else glColor3f(0.0, 0.0, 0.0);
        glVertex2i(row, column);
    }
    glEnd();

    glColor3f(1.0,1.0,0.0);
    displayInfo(16,windowWidth-20);

    glFlush();

    aliveCells = 0;
}

void displayText(GLint x, GLint y, char *text)
{
    unsigned int i;

    glRasterPos2d(x,y);
    for(i=0; i<strlen(text); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void displayInfo(GLint x, GLint y)
{
    char timeString[INFO_SIZE];
    char generationString[INFO_SIZE];
    char aliveCellsString[INFO_SIZE];
    char benchmarkEnabledString[INFO_SIZE];
    char completePercentageString[INFO_SIZE];
    char keyboardInfoString[INFO_SIZE];
    char benchmarkInfoString[INFO_SIZE];
    char gameSizeInfoString[INFO_SIZE];

    char time[INFO_SIZE];
    char gen[INFO_SIZE];
    char alive[INFO_SIZE];

    sprintf(time, "%f", diff);
    sprintf(gen, "%d", generation);
    sprintf(alive, "%d", aliveCells);

    sprintf(timeString, "%s%s ms", "Time: ", time);
    sprintf(generationString, "%s%s", "Generation: ", gen);
    sprintf(aliveCellsString, "%s%s", "Alive cells: ", alive);

    if(canShowInfo) sprintf(keyboardInfoString, "%s", "Press <v> to toggle game's info OFF");
    else sprintf(keyboardInfoString, "%s", "Press <v> to toggle game's info ON");

    if(benchmarkEnabled){
        sprintf(benchmarkInfoString, "Press <b> to turn benchmarking mode OFF");
        sprintf(benchmarkEnabledString, "%s", "Benchmarking mode: [ on ]");
        sprintf(completePercentageString, "%s%f%s", "Benchmarking completion: [ ", fmin(100.0, benchmarkGeneration * 1.0 / ITERATIONS * 100), "% ]");
    }
    else{
        sprintf(benchmarkInfoString, "Press <b> to turn benchmarking mode ON");
        sprintf(benchmarkEnabledString, "%s", "Benchmarking mode: [ off ]");
        sprintf(completePercentageString, "%s", "Benchmarking completion: [ -- ]");
    }
    sprintf(gameSizeInfoString, "Game size: [ %d x %d ]", SIZE, SIZE);

    glPushMatrix();

    displayText(x,y,keyboardInfoString);

    if(canShowInfo)
    {
        displayText(x,y-30, benchmarkInfoString);
        displayText(x,y-60, timeString);
        displayText(x,y-90, generationString);
        displayText(x,y-120, aliveCellsString);
        displayText(x,y-150,benchmarkEnabledString);
        displayText(x,y-180,completePercentageString);
        displayText(x,y-210, gameSizeInfoString);
    }

    glPopMatrix();
}
// Tutorial for OpenGL rendering: https://www.youtube.com/watch?v=QKSa0eYlc5o
