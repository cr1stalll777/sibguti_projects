/*
M – количество операций пересылки.
C– количество операций сравнения
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct OBJ {
    int data;
    struct OBJ* next;
} OBJ;

typedef struct {
    OBJ* head;
    OBJ* tail;
} Queue;


void push_back(int data, Queue* ptr) {
    OBJ* node = calloc(1, sizeof(OBJ));
    node->data = data;

    if(ptr->tail == NULL) {
        ptr->head = ptr->tail = node;
    }
    else {
        ptr->tail->next = node;
        ptr->tail = node;
    }
}

void pop_back(Queue* ptr) {
    if(ptr->tail && ptr->head == ptr->tail) {
        free(ptr->tail);
        ptr->head = ptr->tail = NULL;
    }
    else if(ptr->tail) {
        OBJ* temp = ptr->head;

        while(temp->next && temp->next != ptr->tail) {
            temp = temp->next;
        }

        free(ptr->tail);

        ptr->tail = temp;
        ptr->tail->next = NULL;
    }
}

void push_front(int data, Queue* ptr) {
    OBJ* node = calloc(1, sizeof(OBJ));
    node->data = data;

    if(ptr->head == NULL) {
        ptr->head = ptr->tail = node;
    }
    else {
        node->next = ptr->head;
        ptr->head = node;
    }
}

void pop_front(Queue* ptr) {
    if(ptr->head && ptr->head == ptr->tail) {
        free(ptr->tail);
        ptr->head = ptr->tail = NULL;
    }
    else if(ptr->head) {
        OBJ* temp = ptr->head;
        ptr->head = ptr->head->next;
        free(temp);
    }
}

void show(Queue ptr) {
    OBJ* temp = ptr.head;
    int checksum = 0;
    int series = (ptr.head != NULL) ? 1 : 0;
    printf("Queue: ");
    while (temp) {
        printf("%d ", temp->data);

        // Считаем КР 
        checksum += temp->data;

        // Считаем серии 
        if (temp->next != NULL) {
            if (temp->data > temp->next->data) {
                series++;
            }
        }
        temp = temp->next;
    }
    printf("\nChecksum: %d\n", checksum);
    printf("Series: %d\n", series);


    if(ptr.tail) {
        printf("Head data = %d\nTail data = %d\n", ptr.head->data, ptr.tail->data);
    }
}

int main(void) {

    srand(time(NULL));

    Queue ptr = {NULL};

    // заполнение стека и очереди возрастающими числами
    for (size_t i = 20; i > 0; i--) {
        push_front(i, &ptr);
    }

    show(ptr);

    while (ptr.head != NULL) {
        pop_front(&ptr);
    }

    // заполнение стека и очереди убывающими числами
    printf("---------\n");
    for (size_t i = 1; i < 21; i++) {
        push_front(i, &ptr);
    }

    show(ptr);

    while (ptr.head != NULL) {
        pop_back(&ptr);
    }

    // заполнение стека и очереди случайными числами
    printf("---------\n");
    for (size_t i = 1; i < 21; i++) {
        push_back(rand() % 41 - 20, &ptr);
    }

    show(ptr);

    while (ptr.head != NULL) {
        pop_back(&ptr);
    }
 
    return 0;
}