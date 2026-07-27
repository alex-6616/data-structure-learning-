#include <stdbool.h>
#include <stdio.h>

#define STACK_CAPACITY 4

typedef struct {
    int data[STACK_CAPACITY];
    int top;
} ArrayStack;

// 初始化空栈；此处 top 表示下一个可写位置，也是当前元素个数。
void Init(ArrayStack *stack) {
    stack->top = 0;
}

// top 为 0 时栈为空。
bool IsEmpty(const ArrayStack *stack) {
    return stack->top == 0;
}

// top 到达数组容量时栈满。
bool IsFull(const ArrayStack *stack) {
    return stack->top == STACK_CAPACITY;
}

// 将元素压入栈顶。
bool Push(ArrayStack *stack, int value) {
    if (stack == NULL || IsFull(stack)) {
        return false;
    }
    // 先写入 top 指向的空位，再将 top 加一。
    stack->data[stack->top] = value;
    ++stack->top;
    return true;
}

// 弹出栈顶元素，并可通过 removed 返回其值。
bool Pop(ArrayStack *stack, int *removed) {
    if (stack == NULL || IsEmpty(stack)) {
        return false;
    }
    // top 指向下一空位，所以必须先减一再读取栈顶。
    --stack->top;
    if (removed != NULL) {
        *removed = stack->data[stack->top];
    }
    return true;
}

// 读取栈顶元素但不改变栈。
bool Top(const ArrayStack *stack, int *value) {
    if (stack == NULL || value == NULL || IsEmpty(stack)) {
        return false;
    }
    *value = stack->data[stack->top - 1];  // 实际栈顶下标是 top - 1。
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
