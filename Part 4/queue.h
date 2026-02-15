#ifndef QUEUE_H
#define QUEUE_H

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


void push_back(int data, Queue* ptr);
void pop_back(Queue* ptr);
void push_front(int data, Queue* ptr);
void pop_front(Queue* ptr);
void show(Queue ptr);

#endif