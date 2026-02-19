#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 400

int collisions = 0;

typedef struct {
    char *word;
    int count;
    int is_occupied; 
} Entry;

void insert(Entry* hash_table, char *word);
int search(Entry* hash_table, char *word);
unsigned int hash(char *key);
void clear_table(Entry* hash_table);


int main() {

    Entry hash_table[TABLE_SIZE] = {0};

    FILE* fp = fopen("data.txt", "r");

    char buffer[100];
    while (fscanf(fp, "%99s", buffer) == 1) {
        insert(hash_table, buffer);
    }
    fclose(fp);

    printf("\n+---------------------+--------------------+-----------------+\n");
    printf("|        Метод        | Объем хэш-таблицы  | Число коллизий  |\n");
    printf("+---------------------+--------------------+-----------------+\n");
    printf("| Линейные пробы      | %12lu байт | %15d |\n", (unsigned long)sizeof(hash_table), collisions);
    printf("+---------------------+--------------------+-----------------+\n\n");

    char find_string[100];
    printf("Введите слово, которое ищем:\n");
    scanf("%99s", find_string);

    int count = 0;
    if(count = search(hash_table, find_string)) {
        printf("Слово \"%s\" найдено! В файле записано %d раз(а)\n", find_string, count);
    }
    else {
        printf("Не найдено!\n");
    }

    clear_table(hash_table);
    return 0;
}

void insert(Entry* hash_table, char *word) {
    unsigned int initial_index = hash(word);
    unsigned int index = initial_index;
    int i = 0;

    while (hash_table[index].is_occupied) {
        if (strcmp(hash_table[index].word, word) == 0) {
            hash_table[index].count++; 
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        i++;
        
        if (index == initial_index) return;
    }

    hash_table[index].word = strdup(word);
    hash_table[index].count = 1;
    hash_table[index].is_occupied = 1;
    
    if (i > 0) collisions++;
}

int search(Entry* hash_table, char *word) {
    unsigned int index = hash(word);
    unsigned int start = index;

    while (hash_table[index].is_occupied) {
        if (strcmp(hash_table[index].word, word) == 0)
            return hash_table[index].count;
        
        index = (index + 1) % TABLE_SIZE;
        if (index == start) break;
    }
    return 0;
}

unsigned int hash(char *key) {
    unsigned long int hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % TABLE_SIZE;
}


void clear_table(Entry* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i].is_occupied) {
            free(hash_table[i].word);
        }
    }
}