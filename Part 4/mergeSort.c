#include "queue.h"

/*
M – количество операций пересылки.
C– количество операций сравнения
*/

/*
n – количество элементов в S
a, b – рабочие списки
c=(c0, c1) – массив из двух очередей
count_series – предполагаемый размер серии
q – фактический размер серии в списке a
r – фактический размер серии в списке b
m – текущее количество элементов в списках a и b
i – номер активной очереди

*/

/*
      2          5          0          10         4
    [data]  -> [data]  -> [data]  -> [data]  -> [data]  -> NULL 
    [next] /   [next] /   [next] /   [next] /   [next] /

*/


void moveNode(Queue* dest, Queue* src, int* M);
void mergeToQueue(Queue* a, int q, Queue* b, int r, Queue* c, int* C, int* M);
void mergeSort(Queue* lst, int* C, int* M);
int countSeries(Queue* q);    

int main(void) {

    Queue lst = {0};

    push_back(5, &lst);
    push_back(2, &lst);
    push_back(4, &lst);
    push_back(6, &lst);
    push_back(1, &lst);
    push_back(3, &lst);
    push_back(87, &lst);
    push_back(8, &lst);
    push_back(66, &lst);
    push_back(45, &lst);
    push_back(-123, &lst);
    
    int C = 0, M = 0, before_checksum = 0, after_checksum = 0, before_series = 1, after_series = 1;
    
    // КР до
    OBJ* temp = lst.head;
    while (temp) {
        before_checksum += temp->data;
        temp = temp->next;
    }
    
    before_series = countSeries(&lst);
    
    /*ТУТ АЛГОРИТМ*/
    mergeSort(&lst, &C, &M);
    
    
    // КР после
    temp = lst.head;
    while (temp) {
        after_checksum += temp->data;
        temp = temp->next;
    }

    after_series = countSeries(&lst);


    printf("*** mergeSort ***\nОтсортированная последовательность: ");
    for (OBJ* node = lst.head; node; node = node->next) {
        printf("%d ", node->data);
    }

    printf("\nHEAD: %d\n", lst.head->data);
    printf("TAIL: %d\n", lst.tail->data);
    
    printf("C = %d\nM = %d\nКонтрольная сумма ДО: %d\nКонтрольная сумма ПОСЛЕ: %d\n", C, M, before_checksum, after_checksum);
    printf("К-во серий ДО: %d\nК-во серий ПОСЛЕ: %d\n", before_series, after_series);
    
    
    return 0;
}



void moveNode(Queue* dest, Queue* src, int* M) {
    if (src->head == NULL) return;

    OBJ* node = src->head;
    src->head = node->next;
    if (src->head == NULL) src->tail = NULL;

    node->next = NULL; 

    if (dest->tail == NULL) { 
        dest->head = node;
        dest->tail = node;
    } else { 
        dest->tail->next = node;
        dest->tail = node;
    }
    *M += 3;
}

int countSeries(Queue* q) {
    if (q->head == NULL) return 0;
    int s = 1;
    OBJ* curr = q->head;
    while (curr->next != NULL) {
        if (curr->data > curr->next->data) {
            s++;
        }
        curr = curr->next;
    }
    return s;
}

void mergeToQueue(Queue* a, int q, Queue* b, int r, Queue* c, int* C, int* M) {
    while(q != 0 && r != 0) {
        (*C)++;
        if(a->head->data <= b->head->data) {
            moveNode(c, a, M);
            q--;
        }
        else {
            moveNode(c, b, M);
            r--;            
        }
    }

    while(q > 0) {
        moveNode(c, a, M);
        q--;
    }
    while(r > 0) {
        moveNode(c, b, M);
        r--;
    }
}

void mergeSort(Queue* lst, int* C, int* M) {
    Queue a = {lst->head, NULL};
    Queue b = {lst->head->next, NULL};

    size_t n = 1;

    OBJ* k = a.head;
    OBJ* p = b.head;

    while(p != NULL) {
        n++;
        if(p->next == NULL) {
            a.tail = p;
            b.tail = k;
        }
        k->next = p->next;
        k = p;
        p = p->next;
    }

    int count_series = 1;
    
    Queue c[2];
    while(count_series < n) {
        c[0] = (Queue) {NULL};
        c[1] = (Queue) {NULL};

        int i = 0, m = n;

        while(m > 0) {
            int q = 0, r = 0;

            q = (m >= count_series) ? count_series : m;
            m -= q;

            r = (m >= count_series) ? count_series : m;
            m -= r;

            mergeToQueue(&a, q, &b, r, &c[i], C, M);
            
            i = 1 - i;
        }
        

        a = c[0];
        b = c[1];
        count_series *= 2;
    }
    c[0].tail->next = NULL;
    *lst = c[0];
}