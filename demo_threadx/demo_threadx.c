/* This is a small demo of the high-performance ThreadX kernel.  It includes examples of eight
   threads of different priorities, using a message queue, semaphore, mutex, event flags group, 
   byte pool, and block pool.  */

#include "tx_api.h"
#include "printf.h"
#include <BMI160.h>
#include <GPIOControl.h>
#include <EdVice.h>

#define DEMO_STACK_SIZE         1024
#define DEMO_BYTE_POOL_SIZE     9120
#define DEMO_BLOCK_POOL_SIZE    100
#define DEMO_QUEUE_SIZE         100


/* Define the ThreadX object control blocks...  */

TX_THREAD               thread_0;
TX_QUEUE                queue_0;
TX_SEMAPHORE            semaphore_0;
TX_MUTEX                mutex_0;
TX_EVENT_FLAGS_GROUP    event_flags_0;
TX_BYTE_POOL            byte_pool_0;
TX_BLOCK_POOL           block_pool_0;
UCHAR                   memory_area[DEMO_BYTE_POOL_SIZE];


/* Define the counters used in the demo application...  */

ULONG                   count;


/* Define thread prototypes.  */

void    mainThread(ULONG thread_input);


/* Define main entry point.  */

int main(void)
{
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}


/* Define what the initial system looks like.  */

void    tx_application_define(void *first_unused_memory)
{

CHAR    *pointer;


    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", memory_area, DEMO_BYTE_POOL_SIZE);

    /* Put system definition stuff in here, e.g. thread creates and other assorted
       create information.  */

    /* Allocate the stack for thread 0.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    /* Create the main thread.  */
    tx_thread_create(&thread_0, "thread 0", mainThread, 0,  
            pointer, DEMO_STACK_SIZE, 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}

//! Loads sensor data to the model
void Measure(float* data)
{
    //! Get 512 sets of data from the acceleration sensor
    if (!FillSensorData(data, 512))
        Error();
}


float sensorData[48 * 32];

void LogData(char* msg)
{
    Measure(sensorData);
    for (int i = 0; i < 16 * 32; ++i)
    {
        printf("%g, %g, %g\n", sensorData[3 * i], sensorData[3 * i + 1], sensorData[3 * i + 2]);
    }
}

//! Run model
void RunModel()
{
    //! Detect abnormality with given Inference function
    //! Note how load function (Measure) has been passed as function pointer
   int isAbnormal = Inference(Measure);

    //! Set state as abnormal or normal according to the model output
    if (isAbnormal)
    {
        SetRed(1);
        SetBlue(0);
        SetGreen(1);
        printf("Abnormal\n");
    }
    else
    {
        SetBlue(1);
        SetRed(1);
        SetGreen(0);
        printf("Normal\n");

    }
}

/* Define the test threads.  */

void    mainThread(ULONG thread_input)
{

//UINT    status;
    char msg[50];

    /* This thread simply sits in while-forever-sleep loop.  */
    while(1)
    {

        /* Increment the thread counter.  */
       RunModel();
       //LogData(msg);

    }
}
