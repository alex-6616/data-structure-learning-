#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *CreateEmpty(void) {
    Node *head = malloc(sizeof(Node));
    if (head != NULL) {
        head->next = NULL;
    }
    return head;
}

Node *FindPrevious(Node *head, int index) {
    if (head == NULL || index < 0) {
        return NULL;
    }

    Node *previous = head;
    for (int i = 0; i < index && previous != NULL; ++i) {
        previous = previous->next;
    }
    return previous;
}

bool InsertAt(Node *head, int index, int value) {
    Node *previous = FindPrevious(head, index);
    if (previous == NULL) {
        return false;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->next = previous->next;
    previous->next = node;
    return true;
}

bool DeleteAt(Node *head, int index, int *removed) {
    Node *previous = FindPrevious(head, index);
    if (previous == NULL || previous->next == NULL) {
        return false;
    }

    Node *target = previous->next;
    previous->next = target->next;
    if (removed != NULL) {
        *removed = target->data;
    }
    free(target);
    return true;
}

void Print(const Node *head) {
    for (const Node *p = head->next; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }
}

void Destroy(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = CreateEmpty();
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    InsertAt(head, 0, 10);
    InsertAt(head, 1, 30);
    InsertAt(head, 1, 20);
    Print(head);

    int removed;
    if (DeleteAt(head, 1, &removed)) {
        printf("removed = %d\n", removed);
    }
    Print(head);
    Destroy(head);
    return EXIT_SUCCESS;
}
