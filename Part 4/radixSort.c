#include "queue.h"

/*
M – количество операций пересылки.
C– количество операций сравнения
*/



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

/*
      2          5          0          10         4
    [data]  -> [data]  -> [data]  -> [data]  -> [data]  -> NULL 
    [next] /   [next] /   [next] /   [next] /   [next] /

*/

unsigned char get_byte(int value, int j) {
    return (value >> (8 * j)) & 0xFF;
}

void regexSort(Queue* lst) {

// S - количество чисел
// L - количество цифр в числе
// m - количество очередей (зависит от системы счисления)

    //OBJ *heads[256], *tails[256];

    Queue Q[256];

    size_t L = sizeof(lst->head->data);

    for (int j = L; j > 0; j--)
    {
        for (int i = 0; i < 256; i++) {
            Q[i].head = Q[i].tail = NULL; 
        }
    
        OBJ *p = lst->head;

        while(p) {
            unsigned char d = get_byte(p->data, j);

            if(Q[d].head == NULL) {
                Q[d].head = Q[d].tail = p;
            }
            else { 
                Q[d].tail->next = p;
                Q[d].tail = p;
            }
            p = p->next;
        }
/*
A(10) -> B(20) -> C(10)

Q[10] = A(10)
        /   \    -> next = B(20)
      head  tail

Q[10] = A(10)          C(10)
          |   next->     |    next-> NULL
        head            tail

Q[20] = B(20)
        /   \    -> next = C(10)
      head  tail
*/
        OBJ *newHead = NULL;
        OBJ *lastTail = NULL;

        for (int i = 0; i < 256; i++)
        {
            if(Q[i].head != NULL) {
                if (newHead == NULL) {
                    newHead = Q[i].head;
                    lastTail = Q[i].tail;
                }
                else {
                    lastTail->next = Q[i].head;
                    lastTail = Q[i].tail;
                }
            } 
        }

        if (lastTail != NULL) {
            lastTail->next = NULL;
        }
        lst->head = newHead;
        lst->tail = lastTail;

    }
 
}

int main(void) {

    Queue lst = {0};
    srand(time(NULL));
    for (int i = 0; i < 200; i++) {
        push_back(rand() % 10000, &lst);
    }
    
    int C = 0, M = 0, before_checksum = 0, after_checksum = 0, before_series = 1, after_series = 1;
    
 
    OBJ* temp = lst.head;
    while (temp) {
        before_checksum += temp->data;
        temp = temp->next;
    }
    
    before_series = countSeries(&lst);
    
    regexSort(&lst);

    
    temp = lst.head;
    while (temp) {
        after_checksum += temp->data;
        temp = temp->next;
    }

    after_series = countSeries(&lst);


    printf("*** regexSort ***\nОтсортированная последовательность: ");
    for (OBJ* node = lst.head; node; node = node->next) {
        printf("%d ", node->data);
    }

    printf("\nHEAD: %d\n", lst.head->data);
    printf("TAIL: %d\n", lst.tail->data);
    
    printf("C = %d\nM = %d\nКонтрольная сумма ДО: %d\nКонтрольная сумма ПОСЛЕ: %d\n", C, M, before_checksum, after_checksum);
    printf("К-во серий ДО: %d\nК-во серий ПОСЛЕ: %d\n", before_series, after_series);
    
    
    return 0;
}




