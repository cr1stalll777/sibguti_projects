/*
M – количество операций пересылки.
C– количество операций сравнения
*/


// (n-1) + (n-2) + (n-3) + (n-4) + (n-5) + (n-6) + (n-7) + (n-8) + (n-9)


#include <stdio.h>

int main(void) {

    int arr[] = {-1, -31, -124, 3, -65, 92, 21, 12, -344, 1231};

    int C = 0, M = 0;
    int n = sizeof(arr) / sizeof(*arr);

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        
        for (int j = i + 1; j < n; j++) {
            C++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
        M+=3;
    }

    printf("Отсортированный массив методом selectSort: ");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    
    printf("C = %d\n", C);
    printf("M = %d\n", M);
    
    
    
    return 0;
}
