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



void quick_sort(int arr[], int left, int right, int* C, int* M) {

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

        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*M) += 3;
            i++;
            j--;
        }
    }
    if (left < j) quick_sort(arr, left, j, C, M);
    if (i < right) quick_sort(arr, i, right, C, M);
}



int main(void) {

    int arr[200];
    size_t length = sizeof(arr) / sizeof(*arr);
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 201 - 100;
    }
      
    int C = 0, M = 0, before_checksum = 0, after_checksum = 0, before_series = 1, after_series = 1;
    

    for(size_t i = 0; i < length; ++i) {
        before_checksum += arr[i];
    }


    for (size_t i = 0; i < length - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            before_series++;
        }
    }
    
    quick_sort(arr, 0, length - 1, &C, &M);
    

    for(size_t i = 0; i < length; ++i) {
        after_checksum += arr[i];
    }


    for (size_t i = 0; i < length - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            after_series++;
        }
    }

    printf("*** heapSort ***\nОтсортированный массив: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }

    putchar('\n');
    
    printf("C = %d\nM = %d\nКонтрольная сумма ДО: %d\nКонтрольная сумма ПОСЛЕ: %d\n", C, M, before_checksum, after_checksum);
    printf("К-во серий ДО: %d\nК-во серий ПОСЛЕ: %d\n", before_series, after_series);
    
    
    return 0;
}