#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// 入栈：在链表头部插入新结点，并更新栈顶指针。
bool Push(StackNode **top, int value) {
    if (top == NULL) {
        return false;
    }
    StackNode *node = malloc(sizeof(StackNode));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    // 新结点先连接原栈顶，再成为新的栈顶。
    node->next = *top;
    *top = node;
    return true;
}

// 出栈：删除栈顶结点，并可返回其数据。
bool Pop(StackNode **top, int *removed) {
    if (top == NULL || *top == NULL) {
        return false;
    }
    StackNode *target = *top;
    // 先移动栈顶指针，再释放原栈顶结点。
    *top = target->next;
    if (removed != NULL) {
        *removed = target->data;
    }
    free(target);
    return true;
}

// 读取栈顶元素但不出栈。
bool Top(const StackNode *top, int *value) {
    if (top == NULL || value == NULL) {
        return false;
    }
    *value = top->data;
    return true;
}

// 连续出栈，释放所有结点。
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
