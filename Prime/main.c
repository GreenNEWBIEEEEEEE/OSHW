/*
 * main.c
 * Copyleft (ɔ) 2021 greennewbie <adsl53102@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <pthread.h>
#include <math.h>
int resPrime[300];
int indexPrime = 0;

void* isPrime(void* num)
{
    int* t =(int*) num;
    int target = *t;
    int i = 0;
    int j = 2;
    int flag = 0;
    if (target <= 1)
        pthread_exit(NULL);
    while(j <= target)
    {
        flag = 0;
        for (i = 2; i <= sqrt(j); ++i) {
            if (j % i == 0)
                flag= 1;
        }
        if (!flag)
            resPrime[indexPrime++] = j;
        j++;
    }
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    pthread_t thread;
    pthread_create(&thread, NULL, isPrime, &num);
    pthread_join(thread, NULL);
    int i = 0;
    for (i = 0; i < indexPrime; ++i) {
        printf("%d\n", resPrime[i]);
    }
    return 0;
}
