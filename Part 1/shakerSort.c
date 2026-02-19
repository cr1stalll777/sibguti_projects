#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getChecksum(int *arr, int n);
int getSeries(int *arr, int n);
void shakerSort(int *arr, int n, int *C, int *M);

int main() {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Шейкерная (ShakerSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный массив      | Случайный массив          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int i = 0; i < n_count; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));
        int C_ord, M_ord, C_rand, M_rand;

        for (int j = 0; j < n; j++) arr[j] = j;
        shakerSort(arr, n, &C_ord, &M_ord);

        for (int j = 0; j < n; j++) arr[j] = rand() % 1000 - 500;
        shakerSort(arr, n, &C_rand, &M_rand);

        printf("| %3d | %-10d %-10d     | %-10d %-10d     |\n", 
               n, M_ord, C_ord, M_rand, C_rand);

        free(arr);
    }
    printf("+-----+---------------------------+---------------------------+\n");

    return 0;
}

int getChecksum(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}

int getSeries(int *arr, int n) {
    if (n <= 0) return 0;
    int series = 1;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) series++;
    }
    return series;
}

void shakerSort(int *arr, int n, int *C, int *M) {
    *C = 0; *M = 0;
    int L = 0, R = n - 1, k = n - 1;

    while (L < R) {
        for (int j = R; j > L; j--) {
            (*C)++;
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                k = j;
                *M += 3;
            }
        }
        L = k;
        for (int j = L; j < R; j++) {
            (*C)++;
            if (arr[j + 1] < arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                k = j;
                *M += 3;
            }
        }
        R = k;
    }
}