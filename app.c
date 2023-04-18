#include <stdio.h>
#include <time.h>
#define ROWS 4
#define COLS 4

int main() {
    clock_t start = clock();
    int matrix1[ROWS][COLS] = {{1, 2, 3, 4},
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15, 16}};

    int matrix2[ROWS][COLS] = {{1, 2, 3, 4},
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15, 16}};

    int result[ROWS][COLS] = {0};

    // Multiply the matrices
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            for (int k = 0; k < COLS; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Print the result
    printf("Result matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    clock_t end = clock();
double elapsed_time = ((double) (end - start));
printf("Elapsed time: %f ms", elapsed_time);

    return 0;
}
