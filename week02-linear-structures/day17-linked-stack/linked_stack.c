#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

bool Push(StackNode **top, int value) {
    if (top == NULL) {
        return false;
    }
    StackNode *node = malloc(sizeof(StackNode));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->next = *top;
    *top = node;
    return true;
}

bool Pop(StackNode **top, int *removed) {
    if (top == NULL || *top == NULL) {
        return false;
    }
    StackNode *target = *top;
    *top = target->next;
    if (removed != NULL) {
        *removed = target->data;
    }
    free(target);
    return true;
}

bool Top(const StackNode *top, int *value) {
    if (top == NULL || value == NULL) {
        return false;
    }
    *value = top->data;
    return true;
}

void Clear(StackNode **top) {
    int ignored;
    while (Pop(top, &ignored)) {
    }
}

int main(void) {
    StackNode *top = NULL;
    Push(&top, 10);
    Push(&top, 20);
    Push(&top, 30);

    int value;
    Top(top, &value);
    printf("top = %d\n", value);
    while (Pop(&top, &value)) {
        printf("pop %d\n", value);
    }
    Clear(&top);
    return 0;
}
