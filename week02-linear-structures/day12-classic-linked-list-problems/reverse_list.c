#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 在链表头部插入新结点，并返回新的首结点。
Node *PushFront(Node *first, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return first;
    }
    node->data = value;
    node->next = first;
    return node;
}

// 使用三个指针原地反转单链表，并返回新的首结点。
Node *Reverse(Node *first) {
    Node *previous = NULL;
    Node *current = first;

    while (current != NULL) {
        // 必须先保存后继，否则修改 current->next 后会丢失剩余链表。
        Node *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

// 按链表顺序输出所有元素。
void Print(const Node *first) {
    for (const Node *p = first; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }
}

// 释放整条链表。
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
