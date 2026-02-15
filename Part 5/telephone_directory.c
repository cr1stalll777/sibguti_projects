#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[100];
    char adress[200];
    char phone_nubmer[20];
} Directory;




int main() {


    Directory lst[20] = {0};
    Directory* idxName[20];
    FILE* fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("Ошибка: файл не найден!\n");
        return 0;
    }

    int n = 0;
    while (n < 20 && fscanf(fp, " %99[^;];%199[^;];%19[^\n]", 
                  lst[n].name, 
                  lst[n].adress, 
                  lst[n].phone_nubmer) == 3) {
        idxName[n] = &lst[n];
        n++;
    }
    
    fclose(fp);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(idxName[j]->name, idxName[j + 1]->name) > 0) {
                Directory* temp = idxName[j];
                idxName[j] = idxName[j + 1];
                idxName[j + 1] = temp;
            }
        }
    }

    char* start = "А";
    char* end = "Е";

    int low = 0, high = n - 1;
    int first_index = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (strcmp(idxName[mid]->name, start) >= 0) {
            first_index = mid; 
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("Результаты поиска от %s до %s:\n", start, end);
    if (first_index != -1) {
        for (int i = first_index; i < n; i++) {
            if (strcmp(idxName[i]->name, end) <= 0) {
                printf("%s | %s | %s\n", idxName[i]->name, idxName[i]->adress, idxName[i]->phone_nubmer);
            } else {
                break;
            }
        }
    } else {
        printf("Ничего не найдено\n");
    }
    return 0;
}