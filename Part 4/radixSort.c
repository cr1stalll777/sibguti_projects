#include "linkedList.h"

/*
M – количество операций пересылки.
C– количество операций сравнения
*/

/*
      2          5          0          10         4
    [data]  -> [data]  -> [data]  -> [data]  -> [data]  -> NULL 
    [next] /   [next] /   [next] /   [next] /   [next] /

*/

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

int getChecksum(linkedList* lst);
int countSeries(linkedList* q);
unsigned char get_byte(int value, int j);
void radixSort(linkedList* lst,  int* C, int* M);


int main(void) {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Поразрядная сортировка (RadixSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный список      | Случайный список          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int k = 0; k < n_count; k++) {
        int n = sizes[k];
        linkedList l_ord = {NULL, NULL}, l_rand = {NULL, NULL};
        int C_ord, M_ord, C_rand, M_rand;

        for (int i = 0; i < n; i++) {
            Node* n1 = malloc(sizeof(Node)); n1->data = i; n1->next = NULL;
            if(!l_ord.head) l_ord.head = l_ord.tail = n1; else { l_ord.tail->next = n1; l_ord.tail = n1; }
            
            Node* n2 = malloc(sizeof(Node)); n2->data = rand() % 10000; n2->next = NULL;
            if(!l_rand.head) l_rand.head = l_rand.tail = n2; else { l_rand.tail->next = n2; l_rand.tail = n2; }
        }

        radixSort(&l_ord, &C_ord, &M_ord);
        radixSort(&l_rand, &C_rand, &M_rand);

        printf("| %3d | %-10d %-10d     | %-10d %-10d     |\n", n, M_ord, C_ord, M_rand, C_rand);

        // Очистка памяти
        Node *c1 = l_ord.head, *c2 = l_rand.head;
        while(c1) { Node* t = c1; c1 = c1->next; free(t); }
        while(c2) { Node* t = c2; c2 = c2->next; free(t); }
    }
    printf("+-----+---------------------------+---------------------------+\n");

    return 0;
}

unsigned char get_byte(int value, int j) {
    return (value >> (8 * j)) & 0xFF;
}

void radixSort(linkedList* lst, int* C, int* M) {
    *C = 0; *M = 0;
    if (!lst->head) return;

    linkedList Q[256];
    int L = sizeof(int);

    for (int j = 0; j < L; j++) {
        for (int i = 0; i < 256; i++) {
            Q[i].head = Q[i].tail = NULL;
        }

        Node *p = lst->head;
        while(p) {
            unsigned char d = get_byte(p->data, j);
            if(Q[d].head == NULL) {
                Q[d].head = Q[d].tail = p;
            } else { 
                Q[d].tail->next = p;
                Q[d].tail = p;
            }
            (*M)++;
            p = p->next;
        }

        Node *newHead = NULL;
        Node *lastTail = NULL;

        for (int i = 0; i < 256; i++) {
            if(Q[i].head != NULL) {
                if (newHead == NULL) {
                    newHead = Q[i].head;
                    lastTail = Q[i].tail;
                } else {
                    lastTail->next = Q[i].head;
                    lastTail = Q[i].tail;
                }
                (*M)++;
            }
        }

        if (lastTail != NULL) lastTail->next = NULL;
        lst->head = newHead;
        lst->tail = lastTail;
    }
}

int countSeries(linkedList* q) {
    if (q->head == NULL) return 0;
    int s = 1;
    Node* curr = q->head;
    while (curr->next != NULL) {
        if (curr->data > curr->next->data) {
            s++;
        }
        curr = curr->next;
    }
    return s;
}

int getChecksum(linkedList* lst) {
    int sum = 0;
    Node* curr = lst->head;
    while (curr != NULL) {
        sum += curr->data;
        curr = curr->next;
    }
    return sum;
}