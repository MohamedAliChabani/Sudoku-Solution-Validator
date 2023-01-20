#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9

typedef struct {
    int row;
    int col;
}parameters;

void print_array(int *, int);
void print_grid();

int count_element_in_row(int  *, int);
int count_element_in_col(int [N][N], int, int);

void *check_rows(void *);
void *check_cols(void *);
void *check_box(void *);

#endif
