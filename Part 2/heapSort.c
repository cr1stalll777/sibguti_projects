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
void siftDown(int arr[], int n, int i, int* C, int* M);
void heapSort(int arr[], int n, int* C, int* M);


int main() {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Пирамидальная сортировка (HeapSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный массив      | Случайный массив          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int i = 0; i < n_count; i++) {
        int n = sizes[i];
        int *arr_ord = malloc(n * sizeof(int));
        int *arr_rand = malloc(n * sizeof(int));
        int C_ord, M_ord, C_rand, M_rand;

        // Заполнение упорядоченного массива
        for (int j = 0; j < n; j++) arr_ord[j] = j;
        heapSort(arr_ord, n, &C_ord, &M_ord);

        // Заполнение случайного массива
        for (int j = 0; j < n; j++) arr_rand[j] = rand() % 1000 - 500;
        heapSort(arr_rand, n, &C_rand, &M_rand);

        printf("| %3d | %-10d %-10d     | %-10d %-10d     |\n", 
               n, M_ord, C_ord, M_rand, C_rand);

        free(arr_ord);
        free(arr_rand);
    }
    printf("+-----+---------------------------+---------------------------+\n");

    return 0;
}

void siftDown(int arr[], int n, int i, int* C, int* M) {
    int largest = i;

    int l = 2*i + 1;
    int r = 2*i + 2;


    if(l < n) {
        (*C)++;
        if(arr[largest] < arr[l]) 
            largest = l;
    }
    if(r < n) {
        (*C)++;
        if(arr[largest] < arr[r])
            largest = r;
    }

    if(largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        (*M)+=3;
        siftDown(arr, n, largest, C, M);
    }
}

void heapSort(int arr[], int n, int* C, int* M) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, n, i, C,M);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        (*M)+=3;
        siftDown(arr, i, 0, C, M);
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