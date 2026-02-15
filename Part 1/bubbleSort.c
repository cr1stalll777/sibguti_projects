/*
M – количество операций пересылки.
C– количество операций сравнения
*/


// (n-1) + (n-2) + (n-3) + (n-4) + (n-5) + (n-6) + (n-7) + (n-8) + (n-9)


#include <stdio.h>

int main(void) {

    int arr[] = {-1, -31, -124, 3, -65, 92, 21, 12, -344, 1231};
    //int arr[] = {-344, -124, -65, -31, -1, 3, 12, 21, 92, 1231};



    
    int C = 0, M = 0, before_checksum = 0, after_checksum = 0, before_series = 1, after_series = 1;
    size_t length = sizeof(arr) / sizeof(*arr);

    // КР до
    for(size_t i = 0; i < length; ++i) {
        before_checksum += arr[i];
    }

    // к-во серий ДО
    for (size_t i = 0; i < length - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            before_series++;
        }
    }
    

    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = length - 1; j > i; j--)
        {
            C++;
            if(arr[j] < arr[j-1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                M+=3;
            }
        }
        // КР после
        after_checksum += arr[i];
    }

    // К-во серий ПОСЛЕ
    for (size_t i = 0; i < length - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            after_series++;
        }
    }

    printf("*** bubbleSort ***\nОтсортированный массив: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }

    putchar('\n');
    
    printf("C = %d\nM = %d\nКонтрольная сумма ДО: %d\nКонтрольная сумма ПОСЛЕ: %d\n", C, M, before_checksum, after_checksum);
    printf("К-во серий ДО: %d\nК-во серий ПОСЛЕ: %d\n", before_series, after_series);
    
    
    return 0;
}