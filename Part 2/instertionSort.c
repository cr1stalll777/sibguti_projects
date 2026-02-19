#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getChecksum(int *arr, int n);
int getSeries(int *arr, int n);
void insertionSort(int *arr, int n, int *C, int *M);


int main() {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Сортировка вставками (InsertionSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный массив      | Случайный массив          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int i = 0; i < n_count; i++) {
        int n = sizes[i];
        int *arr_ord = malloc(n * sizeof(int));
        int *arr_rand = malloc(n * sizeof(int));
        int C_ord, M_ord, C_rand, M_rand;

        // Упорядоченный массив
        for (int j = 0; j < n; j++) arr_ord[j] = j;
        insertionSort(arr_ord, n, &C_ord, &M_ord);

        // Случайный массив
        for (int j = 0; j < n; j++) arr_rand[j] = rand() % 1000 - 500;
        insertionSort(arr_rand, n, &C_rand, &M_rand);

        printf("| %3d | %-10d %-10d     | %-10d %-10d     |\n", 
               n, M_ord, C_ord, M_rand, C_rand);

        free(arr_ord);
        free(arr_rand);
    }
    printf("+-----+---------------------------+---------------------------+\n");

    return 0;
}

void insertionSort(int *arr, int n, int *C, int *M) {
    *C = 0; *M = 0;
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        (*M)++;
        int j = i - 1;
        while (j >= 0) {
            (*C)++;
            if (temp < arr[j]) {
                arr[j + 1] = arr[j];
                (*M)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = temp;
        (*M)++;
    }
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