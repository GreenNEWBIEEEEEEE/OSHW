/*
 * main.c
 * Copyleft (ɔ) 2021 greennewbie <adsl53102@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#define MIN_PID 300
#define MAX_PID 5000
#define NUM 10
int *pidArray = NULL;

int allocate_map(void)
{
    if (pidArray)
        return -1;
    int size = MAX_PID - MIN_PID;
    pidArray = (int*) calloc(size, sizeof(int));
    int i = 0;
    while (i < size)
    {
        pidArray[i++] = 0;
    }
    return 1;

}
int allocate_pid(void){
    int i,flag=1;
    for(i=0; i<MAX_PID-MIN_PID; i++){
        if(pidArray[i]==0){
            pidArray[i]=1;
            flag=0;
            break;
        }
    }
    return flag?-1:i + MIN_PID;
}
/*
int allocate_pid(void)
{
    int size = MAX_PID - MIN_PID;
    int i = 0;
    while (i < size)
    {
        if (!pidArray[i])
        {
            pidArray[i] = 1;
            return i + MIN_PID;
        }
    }
    return 1;
}
*/



void release_pid(int pid)
{
    int p = pid - MIN_PID;
    pidArray[p] = 0;
}


void* threadHelper(void* argv)
{
    int thread_id = *((int*)argv);
    //printf("here\n");
    int pid = allocate_pid();
    if (pid == -1)
        printf("allocated_pid error\n");
    else
    {
        printf("Thread %d allocated pid %d\n", thread_id, pid);
        int sleepNum = 1 + rand() % 16;
        sleep(sleepNum);
        printf("Thread %d released pid %d after sleeping %d\n", thread_id, pid, sleepNum);
        release_pid(pid);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    int i = 0;
    if (allocate_map() == -1)
        printf("allocate_map error\n");
    srand(time(NULL));

    pthread_t threads[NUM];
    for (i = 0; i < NUM; i++) {
        pthread_create(&threads[i], NULL, threadHelper, (void*) &i);
    } /* for (i = 0; i < NUM; i++) */

    for (i = 0; i < NUM; ++i) {
        pthread_join(threads[i], NULL);
    }
    free(pidArray);
    return 0;
}


