#include "linkedList.h"

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

int getChecksum(linkedList* lst);
int countSeries(linkedList* q);    
void moveNode(linkedList* dest, linkedList* src, int* M);
void mergeToQueue(linkedList* a, int q, linkedList* b, int r, linkedList* c, int* C, int* M);
void mergeSort(linkedList* lst, int* C, int* M);

int main(void) {
    srand(time(NULL));
    int sizes[] = {10, 50, 100, 200};
    int n_count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Результаты для метода: Сортировка слиянием (MergeSort)\n");
    printf("+-----+---------------------------+---------------------------+\n");
    printf("|  n  | Упорядоченный список      | Случайный список          |\n");
    printf("|     |    M          C           |    M          C           |\n");
    printf("+-----+---------------------------+---------------------------+\n");

    for (int k = 0; k < n_count; k++) {
        int n = sizes[k];
        linkedList l_ord = {NULL, NULL}, l_rand = {NULL, NULL};
        int C_ord = 0, M_ord = 0, C_rand = 0, M_rand = 0;

        for (int i = 0; i < n; i++) {
            push_back(i, &l_ord);

            Node* rnd = malloc(sizeof(Node)); 
            rnd->data = rand() % 1000 - 500; 
            rnd->next = NULL;
            if(!l_rand.head) {
                l_rand.head = l_rand.tail = rnd; 
            }
            else {
                l_rand.tail->next = rnd; l_rand.tail = rnd; 
            }
        }

        mergeSort(&l_ord, &C_ord, &M_ord);
        mergeSort(&l_rand, &C_rand, &M_rand);

        printf("| %3d | %-10d %-10d     | %-10d %-10d     |\n", n, M_ord, C_ord, M_rand, C_rand);

        while(l_ord.head) {
            Node* t = l_ord.head; 
            l_ord.head = l_ord.head->next; 
            free(t);
        }

        while(l_rand.head) {
            Node* t = l_rand.head;
            l_rand.head = l_rand.head->next;
            free(t);
        }

    }
    printf("+-----+---------------------------+---------------------------+\n");
    return 0;
}



void moveNode(linkedList* dest, linkedList* src, int* M) {
    if (src->head == NULL) return;

    Node* node = src->head;
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

void mergeToQueue(linkedList* a, int q, linkedList* b, int r, linkedList* c, int* C, int* M) {
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

void mergeSort(linkedList* lst, int* C, int* M) {
    linkedList a = {lst->head, NULL};
    linkedList b = {lst->head->next, NULL};

    size_t n = 1;

    Node* k = a.head;
    Node* p = b.head;

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
    
    linkedList c[2];
    while(count_series < n) {
        c[0] = (linkedList) {NULL};
        c[1] = (linkedList) {NULL};

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