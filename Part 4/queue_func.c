#include "linkedList.h"

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