#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 创建只含头结点的空链表。
Node *CreateEmpty(void) {
    Node *head = malloc(sizeof(Node));
    if (head != NULL) {
        head->next = NULL;
    }
    return head;
}

// 找到下标 index 对应数据结点的前驱；头结点视为第 0 个前驱。
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

// 在第 index 个位置插入新结点。
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
    // 先让新结点接上后继，再修改前驱；顺序相反会丢失原链。
    node->next = previous->next;
    previous->next = node;
    return true;
}

// 删除第 index 个数据结点，并可返回被删元素。
bool DeleteAt(Node *head, int index, int *removed) {
    Node *previous = FindPrevious(head, index);
    if (previous == NULL || previous->next == NULL) {
        return false;
    }

    Node *target = previous->next;
    // 先绕过目标结点完成断链，再读取数据并释放目标结点。
    previous->next = target->next;
    if (removed != NULL) {
        *removed = target->data;
    }
    free(target);
    return true;
}

// 输出带头结点单链表中的所有数据元素。
void Print(const Node *head) {
    for (const Node *p = head->next; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }
}

// 释放所有结点，包括头结点。
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
