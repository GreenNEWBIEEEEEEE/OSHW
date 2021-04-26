/*
 * main.c
 * Copyleft (ɔ) 2021 greennewbie <adsl53102@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int map[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

int resGrid= 0;
int resRow= 0;
int resCol = 0;

typedef struct{
    int row;
    int col;
} Coordinate;

void* checkVertical(void* data)
{
    Coordinate* t = (Coordinate*) data;
    int col = t->col;
    int visited[9];
    int i = 0;
    for (i = 0; i < 9; i++)
        visited[i] = 0;

    for (i = 0; i < 9; i++)
    {
        if (visited[map[i][col] - 1] != 0)
        {
            resCol = 1;
            pthread_exit(NULL);
        }
        visited[map[i][col] - 1] = 1;
    }
}

void* checkRow(void* data)
{
    Coordinate* t = (Coordinate*) data;
    int row = t->row;
    int visited[9];
    int i = 0;
    for (i = 0; i < 9; i++)
        visited[i] = 0;

    for (i = 0; i < 9; i++)
    {
        if (visited[map[row][i] - 1] != 0)
        {
            resRow = 1;
            pthread_exit(NULL);
        }
        visited[map[row][i] - 1] = 1;
    }
}


void* checkGrid(void* data)
{
    Coordinate* t = (Coordinate*) data;
    int col = t->col;
    int row = t->row;
    int visited[9];
    int i = 0;
    int j = 0;
    for (i = 0; i < 9; i++)
        visited[i] = 0;

    for (i = row; i < row + 3; ++i) {
        for (j = col; j < col + 3; ++j) {
            if (visited[map[i][j] - 1] != 0)
            {
                resGrid = 1;
                pthread_exit(NULL);
            }
            visited[map[i][j] - 1];
        }
    }
    pthread_exit(NULL);
}


int main()
{
    int threadCount = 0;
    pthread_t thread[27];
    int i = 0, j = 0;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            
            Coordinate* t = (Coordinate*) malloc(sizeof(Coordinate));
            t->row = i;
            t->col = j;
            if (i == 0)
                pthread_create(&thread[threadCount++], NULL, checkVertical, t);

            if (j == 0)
                pthread_create(&thread[threadCount++], NULL, checkRow, t);

            if (i % 3 == 0 && j % 3 == 0)
                pthread_create(&thread[threadCount++], NULL, checkGrid, t);
        }
    }
    for (i = 0; i < threadCount; ++i) {
        pthread_join(thread[i], NULL);
    }
    
    if (resCol || resGrid || resRow)
    {
        printf("Invalid %d %d %d\n", resCol,resGrid,resRow);
        return 1;
    }
    printf("Valid\n"); 
    return 0;
}


