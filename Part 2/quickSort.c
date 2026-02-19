/*
M – количество операций пересылки.
C– количество операций сравнения

test
int arr[] = {5, 2, 4, 6, 1, 3};
//int arr[] = {15,2,48,15,0,-5,99,101,7,12,88,33,22,1,5,42,67,9,11,-15};
//int arr[] = {1231, -344, 12, 21, 92, -65, 3, -124, -31, -1}; // обратный порядок для сравнения
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getChecksum(int *arr, int n);
int getSeries(int *arr, int n);
void quickSort(int arr[], int left, int right, int* C, int* M);


int main(void) {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Быстрая сортировка (QuickSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный массив      | Случайный массив          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int k = 0; k < n_count; k++) {
        int n = sizes[k];
        int *arr_ord = malloc(n * sizeof(int));
        int *arr_rand = malloc(n * sizeof(int));
        
        int C_ord = 0, M_ord = 0;
        int C_rand = 0, M_rand = 0;

        // Тест на упорядоченном массиве
        for (int i = 0; i < n; i++) arr_ord[i] = i;
        quickSort(arr_ord, 0, n - 1, &C_ord, &M_ord);

        // Тест на случайном массиве
        for (int i = 0; i < n; i++) arr_rand[i] = rand() % 1000 - 500;
        quickSort(arr_rand, 0, n - 1, &C_rand, &M_rand);

        printf("| %3d | %-10d %-10d     | %-10d %-10d     |\n", 
               n, M_ord, C_ord, M_rand, C_rand);

        free(arr_ord);
        free(arr_rand);
    }
    printf("+-----+---------------------------+---------------------------+\n");

    return 0;
}


void quickSort(int arr[], int left, int right, int* C, int* M) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while(i <= j) {
        while (arr[i] < pivot) {
            (*C)++;
            i++;
        }
        (*C)++;

        while (arr[j] > pivot) {
            (*C)++;
            j--;
        }
        (*C)++;

        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*M) += 3;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(arr, left, j, C, M);
    if (i < right) quickSort(arr, i, right, C, M);
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