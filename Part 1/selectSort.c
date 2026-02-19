#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getChecksum(int *arr, int n);
int getSeries(int *arr, int n);
void selectSort(int *arr, int n, int *C, int *M);

int main() {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Прямой выбор (SelectSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный массив      | Случайный массив          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int i = 0; i < n_count; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));
        int C_ord, M_ord, C_rand, M_rand;

        for (int j = 0; j < n; j++) arr[j] = j;
        selectSort(arr, n, &C_ord, &M_ord);

        for (int j = 0; j < n; j++) arr[j] = rand() % 1000;
        selectSort(arr, n, &C_rand, &M_rand);

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

void selectSort(int *arr, int n, int *C, int *M) {
    *C = 0; *M = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*C)++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
        *M += 3;
    }
}
