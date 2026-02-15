/*
M – количество операций пересылки.
C– количество операций сравнения
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    int arr[200];
    size_t length = sizeof(arr) / sizeof(*arr);
    srand(time(NULL)); // Инициализация генератора временем

    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 201 - 100; // Числа от -100 до 100
    }


    int C = 0, M = 0, before_checksum = 0, after_checksum = 0, before_series = 1, after_series = 1;

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
    
    /*ТУТ АЛГОРИТМ*/
    for (size_t i = 1; i < length; i++)
    //[5, 2, 4, 6, 1, 3]

    //[1 2 3 4 5 6]
    {
        int temp = arr[i]; // 3 // i = 5
        M++;

        int j = i - 1; // 6 // j = 4
        while (j >= 0) {
            C++;
            if(temp < arr[j]) {
                arr[j + 1] = arr[j]; // 2 = 5
                M++;
                j--;
            }
            else {
                break;
            }
        }
        
        arr[j + 1] = temp;
        M++;
    }
    

    
    // КР после
    for(size_t i = 0; i < length; ++i) {
        after_checksum += arr[i];
    }

    // К-во серий ПОСЛЕ
    for (size_t i = 0; i < length - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            after_series++;
        }
    }

    printf("*** instertionSort ***\nОтсортированный массив: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }

    putchar('\n');
    
    printf("C = %d\nM = %d\nКонтрольная сумма ДО: %d\nКонтрольная сумма ПОСЛЕ: %d\n", C, M, before_checksum, after_checksum);
    printf("К-во серий ДО: %d\nК-во серий ПОСЛЕ: %d\n", before_series, after_series);
    
    
    return 0;
}