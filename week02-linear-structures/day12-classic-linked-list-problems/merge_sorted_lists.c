#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 在 tail 之后追加新结点，并更新尾指针。
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

// 使用尾插法创建不带头结点的单链表。
Node *Create(const int values[], int count) {
    // dummy 是临时哨兵结点，可统一处理空表和首结点插入。
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

// 原地合并两个升序链表，不创建新的数据结点。
Node *Merge(Node *left, Node *right) {
    Node dummy = {0, NULL};
    Node *tail = &dummy;

    while (left != NULL && right != NULL) {
        // 每次摘下较小的结点接到结果链表尾部。
        if (left->data <= right->data) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    // 某条链表剩余部分本身有序，可以直接整体接到末尾。
    tail->next = left != NULL ? left : right;
    return dummy.next;
}

// 输出不带头结点的单链表。
void Print(const Node *first) {
    for (const Node *p = first; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }
}

// 逐个释放链表结点。
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
