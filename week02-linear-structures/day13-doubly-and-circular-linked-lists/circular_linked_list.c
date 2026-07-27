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
        head->next = head;
    }
    return head;
}

bool PushBack(Node *head, int value) {
    if (head == NULL) {
        return false;
    }

    Node *tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->next = head;
    tail->next = node;
    return true;
}

void PrintOnce(const Node *head) {
    const Node *p = head->next;
    while (p != head) {
        printf("%d%s", p->data, p->next == head ? "\n" : " -> ");
        p = p->next;
    }
}

void Destroy(Node *head) {
    if (head == NULL) {
        return;
    }
    Node *p = head->next;
    while (p != head) {
        Node *next = p->next;
        free(p);
        p = next;
    }
    free(head);
}

int main(void) {
    Node *head = CreateEmpty();
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    PushBack(head, 10);
    PushBack(head, 20);
    PushBack(head, 30);
    PrintOnce(head);
    Destroy(head);
    return EXIT_SUCCESS;
}
