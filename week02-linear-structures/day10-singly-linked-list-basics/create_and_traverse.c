#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 使用尾插法由数组创建带头结点的单链表。
Node *CreateFromArray(const int values[], int count) {
    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        return NULL;
    }
    head->next = NULL;

    Node *tail = head;  // tail 始终指向当前链表的最后一个结点。
    for (int i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(Node));
        if (node == NULL) {
            // 创建中途失败时，必须释放已经申请的全部结点。
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

// 统计数据结点数量；头结点不计入长度。
int Length(const Node *head) {
    int length = 0;
    for (const Node *p = head->next; p != NULL; p = p->next) {
        ++length;
    }
    return length;
}

// 按值查找首个匹配的数据结点。
const Node *Find(const Node *head, int value) {
    for (const Node *p = head->next; p != NULL; p = p->next) {
        if (p->data == value) {
            return p;
        }
    }
    return NULL;
}

// 从第一个数据结点开始依次遍历并输出。
void Print(const Node *head) {
    for (const Node *p = head->next; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }
}

// 释放整个链表，包括头结点。
void Destroy(Node *head) {
    while (head != NULL) {
        // 必须先保存后继地址，再释放当前结点。
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
