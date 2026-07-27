#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *CreateFromArray(const int values[], int count) {
    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        return NULL;
    }
    head->next = NULL;

    Node *tail = head;
    for (int i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(Node));
        if (node == NULL) {
            Node *current = head;
            while (current != NULL) {
                Node *next = current->next;
                free(current);
                current = next;
            }
            return NULL;
        }
        node->data = values[i];
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return head;
}

int Length(const Node *head) {
    int length = 0;
    for (const Node *p = head->next; p != NULL; p = p->next) {
        ++length;
    }
    return length;
}

const Node *Find(const Node *head, int value) {
    for (const Node *p = head->next; p != NULL; p = p->next) {
        if (p->data == value) {
            return p;
        }
    }
    return NULL;
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
    const int values[] = {12, 25, 37, 49};
    Node *head = CreateFromArray(values, 4);
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    Print(head);
    printf("length = %d, find 37 = %s\n",
           Length(head), Find(head, 37) != NULL ? "yes" : "no");
    Destroy(head);
    return EXIT_SUCCESS;
}
