#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *PushFront(Node *first, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return first;
    }
    node->data = value;
    node->next = first;
    return node;
}

Node *Reverse(Node *first) {
    Node *previous = NULL;
    Node *current = first;

    while (current != NULL) {
        Node *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

void Print(const Node *first) {
    for (const Node *p = first; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }
}

void Destroy(Node *first) {
    while (first != NULL) {
        Node *next = first->next;
        free(first);
        first = next;
    }
}

int main(void) {
    Node *first = NULL;
    for (int value = 4; value >= 1; --value) {
        first = PushFront(first, value);
    }

    Print(first);
    first = Reverse(first);
    Print(first);
    Destroy(first);
    return 0;
}
