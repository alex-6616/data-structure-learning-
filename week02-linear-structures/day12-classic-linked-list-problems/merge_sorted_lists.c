#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *Append(Node **tail, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    (*tail)->next = node;
    *tail = node;
    return node;
}

Node *Create(const int values[], int count) {
    Node dummy = {0, NULL};
    Node *tail = &dummy;
    for (int i = 0; i < count; ++i) {
        if (Append(&tail, values[i]) == NULL) {
            Node *p = dummy.next;
            while (p != NULL) {
                Node *next = p->next;
                free(p);
                p = next;
            }
            return NULL;
        }
    }
    return dummy.next;
}

Node *Merge(Node *left, Node *right) {
    Node dummy = {0, NULL};
    Node *tail = &dummy;

    while (left != NULL && right != NULL) {
        if (left->data <= right->data) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    tail->next = left != NULL ? left : right;
    return dummy.next;
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
    const int a[] = {1, 4, 7};
    const int b[] = {2, 3, 8};
    Node *left = Create(a, 3);
    Node *right = Create(b, 3);

    Node *merged = Merge(left, right);
    Print(merged);
    Destroy(merged);
    return 0;
}
