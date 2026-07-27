#include <stdbool.h>
#include <stdio.h>

#define STACK_CAPACITY 4

typedef struct {
    int data[STACK_CAPACITY];
    int top;
} ArrayStack;

void Init(ArrayStack *stack) {
    stack->top = 0;
}

bool IsEmpty(const ArrayStack *stack) {
    return stack->top == 0;
}

bool IsFull(const ArrayStack *stack) {
    return stack->top == STACK_CAPACITY;
}

bool Push(ArrayStack *stack, int value) {
    if (stack == NULL || IsFull(stack)) {
        return false;
    }
    stack->data[stack->top] = value;
    ++stack->top;
    return true;
}

bool Pop(ArrayStack *stack, int *removed) {
    if (stack == NULL || IsEmpty(stack)) {
        return false;
    }
    --stack->top;
    if (removed != NULL) {
        *removed = stack->data[stack->top];
    }
    return true;
}

bool Top(const ArrayStack *stack, int *value) {
    if (stack == NULL || value == NULL || IsEmpty(stack)) {
        return false;
    }
    *value = stack->data[stack->top - 1];
    return true;
}

int main(void) {
    ArrayStack stack;
    Init(&stack);
    Push(&stack, 10);
    Push(&stack, 20);
    Push(&stack, 30);

    int value;
    Top(&stack, &value);
    printf("top = %d\n", value);
    while (Pop(&stack, &value)) {
        printf("pop %d\n", value);
    }
    printf("empty = %s\n", IsEmpty(&stack) ? "yes" : "no");
    return 0;
}
