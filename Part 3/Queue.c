/*
M – количество операций пересылки.
C– количество операций сравнения
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} linkedList;


void push_back(int data, linkedList* ptr) {
    Node* node = calloc(1, sizeof(Node));
    node->data = data;

    if(ptr->tail == NULL) {
        ptr->head = ptr->tail = node;
    }
    else {
        ptr->tail->next = node;
        ptr->tail = node;
    }
}

void pop_back(linkedList* ptr) {
    if(ptr->tail && ptr->head == ptr->tail) {
        free(ptr->tail);
        ptr->head = ptr->tail = NULL;
    }
    else if(ptr->tail) {
        Node* temp = ptr->head;

        while(temp->next && temp->next != ptr->tail) {
            temp = temp->next;
        }

        free(ptr->tail);

        ptr->tail = temp;
        ptr->tail->next = NULL;
    }
}

void push_front(int data, linkedList* ptr) {
    Node* node = calloc(1, sizeof(Node));
    node->data = data;

    if(ptr->head == NULL) {
        ptr->head = ptr->tail = node;
    }
    else {
        node->next = ptr->head;
        ptr->head = node;
    }
}

void pop_front(linkedList* ptr) {
    if(ptr->head && ptr->head == ptr->tail) {
        free(ptr->tail);
        ptr->head = ptr->tail = NULL;
    }
    else if(ptr->head) {
        Node* temp = ptr->head;
        ptr->head = ptr->head->next;
        free(temp);
    }
}

void show(linkedList ptr) {
    Node* temp = ptr.head;
    int checksum = 0;
    int series = (ptr.head != NULL) ? 1 : 0;
    printf("linkedList: ");
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

    linkedList ptr = {NULL};

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