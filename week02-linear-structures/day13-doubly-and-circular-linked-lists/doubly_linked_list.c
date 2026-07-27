#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node head;
    Node tail;
} DoublyList;

void Init(DoublyList *list) {
    list->head.next = &list->tail;
    list->head.prev = NULL;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
}

bool InsertBefore(Node *position, int value) {
    if (position == NULL || position->prev == NULL) {
        return false;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->prev = position->prev;
    node->next = position;
    position->prev->next = node;
    position->prev = node;
    return true;
}

bool Delete(Node *node, int *removed) {
    if (node == NULL || node->prev == NULL || node->next == NULL) {
        return false;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (removed != NULL) {
        *removed = node->data;
    }
    free(node);
    return true;
}

void PrintForward(const DoublyList *list) {
    for (const Node *p = list->head.next; p != &list->tail; p = p->next) {
        printf("%d%s", p->data, p->next == &list->tail ? "\n" : " <-> ");
    }
}

void PrintBackward(const DoublyList *list) {
    for (const Node *p = list->tail.prev; p != &list->head; p = p->prev) {
        printf("%d%s", p->data, p->prev == &list->head ? "\n" : " <-> ");
    }
}

void Clear(DoublyList *list) {
    Node *p = list->head.next;
    while (p != &list->tail) {
        Node *next = p->next;
        free(p);
        p = next;
    }
    Init(list);
}

int main(void) {
    DoublyList list;
    Init(&list);
    InsertBefore(&list.tail, 10);
    InsertBefore(&list.tail, 20);
    InsertBefore(&list.tail, 30);
    PrintForward(&list);
    PrintBackward(&list);

    int removed;
    Delete(list.head.next->next, &removed);
    printf("removed = %d\n", removed);
    PrintForward(&list);
    Clear(&list);
    return 0;
}
