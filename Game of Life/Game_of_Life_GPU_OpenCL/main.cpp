#include <GL/gl.h>
#include <GL/glut.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include <string.h>
#include <math.h>

#include "Globals.h"
#include "Constants.h"
#include "DeviceKernels.h"
#include "Patterns.h"

#include "Utils.h"

#include "Platform.h"
#include "Device.h"

#include "Context.h"
#include "CommandQueue.h"
#include "MemoryObject.h"
#include "Program.h"
#include "Kernel.h"

#include "Enqueue.h"
#include "Profile.h"

/* OpenGL specific functions. */
void glInit(int argc, char **argv);
void initTexture();
void displayText(GLint x, GLint y, char *text);
void displayInfo(GLint x, GLint y);
void display(void);
void idle(void);
void displayInfo(GLint x, GLint y);

/* Time calculation variables. */
double nanoSeconds;
int generation = 0;
size_t aliveCells = 0;

/*File to save time results. */
bool benchmarkEnabled = false;
bool isFileClosed = false;
bool fileFirstOpened = false;
int benchmarkGeneration = 0;
int numOfBenchmarkFiles = 1;
char saveFileName[FILENAME_SIZE] = "benchmarkTestFile";
FILE *saveFile;


/*The grid the will host the game.*/
const size_t width = SIZE;
const size_t height = SIZE;
const size_t gameSize = SIZE * SIZE;
size_t workGroupSize = WORK_GROUP_SIZE;

grid_t inGrid[gameSize];
grid_t outGrid[gameSize];

/* Platform variables */
cl_uint num_platforms;
cl_platform_id platforms[PLATFORM_ENTRIES];
char info[INFO_BUFFER];

/* Devices variables */
cl_device_id devices[DEVICE_ENTRIES];
cl_device_id device;
cl_uint num_devices;

/* Context variables */
cl_context context;

/* Command queue variables */
cl_command_queue commandQueue;

/* Event object to be used for measuring kernel execution time. */
cl_event event;
cl_ulong before, after;

/* Memory objects */
cl_mem inputMem;
cl_mem outputMem;

/* Program object */
cl_program program;

/* Kernel object */
cl_kernel kernel;
const char kernelName[] = "life";

/* Change the value of this variable based on the kernel strings in DeviceKernels.h. */
const char *source = gameOfLife2;

const char *kernelSource[] = {source};
size_t sourceLength = strlen(gameOfLife2);

const char *patternFileName = NULL;

/* OpenGL variables */
bool canUpdate = false;
bool canRender = false;
bool canShowInfo = true;

/* OpenGL related functions declarations. */
void glInit(int argc, char **argv);
void changeInfoView(unsigned char key, int x, int y);
void idle(void);
void display(void);
void displayText(GLint x, GLint y, char *text);

int main(int argc, char **argv)
{

    /* Creating the grid. */
    printf("Initializing grids...\n");
    linearInitGrid(inGrid);

    /* Filling cells randomly in grid. */
    printf("Filling source grid...\n");
    linearFillGrid(inGrid, patternFileName);

    /* Getting platform info and finding the correct one. */
    getPlatforms(0, NULL, &num_platforms);
    printf("Retrieving information successfull.\n");
    printf("Number of platforms: %d\n\n", num_platforms);
    getPlatforms(num_platforms, platforms, NULL);
    printf("All platform info: \n\n");
    getAllPlatformInfo(num_platforms, platforms, INFO_BUFFER, info, NULL);

    /* Getting device info and finding the correct one. */
    printf("Getting device info...\n");
    getDevices(platforms[1], CL_DEVICE_TYPE_GPU, 1, &device, &num_devices);
    getAllDeviceInfo(device,INFO_BUFFER);

    /* Creating a context. */
    printf("Creating context...\n");
    context = createContext(NULL, num_devices, &device);

    /* Creating command queue. */
    printf("Creating command queue...\n");
    commandQueue = createCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE);

    /* Creating memory objects */
    printf("Creating memory objects...\n");
    inputMem = createBuffer(context, CL_MEM_READ_ONLY, sizeof(inGrid), NULL);
    outputMem = createBuffer(context, CL_MEM_WRITE_ONLY, sizeof(outGrid), NULL);

    /* Creating program object and build it. */
    printf("Creating program...\n");
    program = createProgramWithSource(context, kernelSource, &sourceLength);

    printf("Building program...\n");
    buildProgram(program, 1, &device, "");
    size_t logSize;
    getProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    char *log = (char *)malloc(logSize);
    getProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
    printf("Build log: \n%s\n", log);

    /* Creating kernel object and setting arguments. */
    printf("Setting up kernel...\n");
    kernel = createKernel(program, kernelName);
    setKernelArg(kernel, 0, sizeof(cl_mem), &inputMem);
    setKernelArg(kernel, 1, sizeof(cl_mem), &outputMem);
    setKernelArg(kernel, 2, sizeof(unsigned int), &height);
    setKernelArg(kernel, 3, sizeof(unsigned int), &width);

    glInit(argc, argv);

    releaseMemObject(inputMem);
    releaseMemObject(outputMem);
    releaseKernel(kernel);
    releaseProgram(program);
    releaseCommandQueue(commandQueue);
    releaseContext(context);

    return 0;
}


void glInit(int argc, char **argv){

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
}

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

    if(canUpdate){

        enqueueWriteBuffer(commandQueue, inputMem, CL_FALSE, 0, sizeof(inGrid), inGrid, 0, NULL, NULL);

        enqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &gameSize, &workGroupSize, 0, NULL, &event);

        waitForEvents(1, &event);
        finish(commandQueue);

        generation++;

        getEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(before), &before, NULL);
        getEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(after), &after, NULL);

        nanoSeconds = (after - before) / 1000000.0;

        if(benchmarkEnabled){
            if(!fileFirstOpened){
                char numOfBenchmarkFilesString[STRING_SIZE];
                itoa(numOfBenchmarkFiles, numOfBenchmarkFilesString, 10);
                strcat(saveFileName, numOfBenchmarkFilesString);
                saveFile = initRecordFile(saveFileName);
                memset(saveFileName,0,sizeof(saveFileName));
                strcpy(saveFileName, "benchmarkTestFile");
                fileFirstOpened = true;
                numOfBenchmarkFiles++;
            }

            if(benchmarkGeneration <= ITERATIONS-1){
                fprintf(saveFile,"%f\n",nanoSeconds);
                benchmarkGeneration++;
            }

            else{
                if(!isFileClosed){
                    fclose(saveFile);
                    isFileClosed = true;
                }
                fileFirstOpened = false;
                benchmarkEnabled = false;
                benchmarkGeneration = 0;
            }
        }
        else{
            fileFirstOpened = false;
            benchmarkGeneration = 0;
        }

        enqueueReadBuffer(commandQueue, outputMem, CL_TRUE, 0, sizeof(outGrid), outGrid, 0, NULL, NULL);

        memcpy(inGrid, outGrid, sizeof(inGrid));

        canUpdate = false;
        canRender = true;
    }

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
    for(pos=0; pos<SIZE * SIZE; pos++){
        row = pos % SIZE;
        column = pos / SIZE;
        if(inGrid[pos]==ALIVE){
            glColor3f(0.0, 0.6, 0.0);
            aliveCells++;
        }
        else glColor3f(0.0, 0.0, 0.0);
        glVertex2i(row, column);
    }
    glEnd();

    glColor3f(1.0,1.0,0.0);
    displayInfo(16,windowHeight-20);

    glFlush();

    canRender = false;
    canUpdate = true;
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

    sprintf(time, "%f", nanoSeconds);
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
        sprintf(completePercentageString, "%s%f%s", "Benchmarking completion: [", fmin(100.0,(benchmarkGeneration * 1.0 / ITERATIONS) * 100), "% ]");
    }
    else{
        sprintf(benchmarkInfoString, "Press <b> to turn benchmarking mode ON");
        sprintf(benchmarkEnabledString, "%s", "Benchmarking mode: [ off ]");
        sprintf(completePercentageString, "%s", "Benchmarking completion: [ -- ]");
    }
    sprintf(gameSizeInfoString, "Game size: [ %d x %d ]", SIZE, SIZE);

    glPushMatrix();

     displayText(x,y,keyboardInfoString);

     if(canShowInfo){
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
