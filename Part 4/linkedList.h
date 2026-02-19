#ifndef LIST_H
#define LIST_H

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


void push_back(int data, linkedList* ptr);
void pop_back(linkedList* ptr);
void push_front(int data, linkedList* ptr);
void pop_front(linkedList* ptr);
void show(linkedList ptr);

#endif