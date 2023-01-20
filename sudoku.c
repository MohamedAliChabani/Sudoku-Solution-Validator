#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#include "sudoku.h"

int grid[N][N] ={
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6},
    };

//int grid[9][9] = {
//    {9, 8, 7, 6, 5, 4, 3, 2, 1},
//    {8, 7, 6, 5, 4, 3, 2, 1, 9},
//    {7, 6, 5, 4, 3, 2, 1, 9, 8},
//    {6, 5, 4, 3, 2, 1, 9, 8, 7},
//    {5, 4, 3, 2, 1, 9, 8, 7, 6},
//    {4, 3, 2, 1, 9, 8, 7, 6, 5},
//    {3, 2, 1, 9, 8, 7, 6, 5, 4},
//    {2, 1, 9, 8, 7, 6, 5, 4, 3},
//    {1, 9, 8, 7, 6, 5, 4, 3, 2}
//};
//

bool valid_grid = true;


void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_grid()
{
    for (int i = 0; i < N; i++) {
        print_array(grid[i], N);
    }
}


int count_element_in_row(int *arr, int n)
{
    int counter = 0;

    for (int i = 0; i < N; i++) {
        if (arr[i] == n)
            counter++;
        }

    return counter;
}

int count_element_in_col(int arr[N][N],int col, int n)
{
    int counter = 0;

    for (int i = 0; i < N; i++) {
        if (arr[i][col] == n)
            counter++;
    }

    return counter;
}

void *check_rows(void *p)
{
    parameters *d = (parameters *) p;

    for (int i = 1; i <= N; i++) {
        if (count_element_in_row(grid[d->row], i) != 1) {
            valid_grid = false;
        }
    }
    pthread_exit(0);
}

void *check_cols(void *p)
{
    parameters *d = (parameters *) p;

    for (int i = 1; i <= N; i++) {
        if (count_element_in_col(grid, d->col, i) != 1) {
            valid_grid = false;
        }
    }
    pthread_exit(0);
}


void *check_box(void *p)
{
    parameters *d = (parameters *) p;
    int numbers[N];
    int k = 0;

    // Fill the numbers array with evvery number inside the box
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            numbers[k] = grid[d->row + i][d->col + j];
            k++;
        }
    }

    // Count the occurence of numbers (1 - 9) in the box
    for (int i = 1; i <= N; i++) {
        if (count_element_in_row(numbers, i) != 1) {
            valid_grid = false;
            pthread_exit(0);
        }
    }
    
    pthread_exit(0);
}


int main()
{
    print_grid();
    pthread_t thread_row, thread_col, thread_box;
    parameters p;

    int i = 0;
    int j = 0;

    while (valid_grid == true && i < N) {
        p.row = i;
        p.col = j;

        pthread_create(&thread_row, NULL, check_rows, &p);
        pthread_create(&thread_col, NULL, check_cols, &p);

        if (i % 3 == 0 && j % 3 == 0) {
            pthread_create(&thread_box, NULL, check_box, &p);
        }

        pthread_join(thread_row, NULL);
        pthread_join(thread_col, NULL);
        pthread_join(thread_box, NULL);

        i++;
        j++;
    }

    if (valid_grid)
        printf("Valid\n");
    else {
        printf("Invalid\n");
    }

    return 0;
}
