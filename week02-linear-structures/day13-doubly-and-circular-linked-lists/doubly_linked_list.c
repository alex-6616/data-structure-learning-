#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node head;
    Node tail;
} DoublyList;

// 初始化带头、尾哨兵结点的空双向链表。
void Init(DoublyList *list) {
    list->head.next = &list->tail;
    list->head.prev = NULL;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
}

// 在 position 结点之前插入新结点。
bool InsertBefore(Node *position, int value) {
    if (position == NULL || position->prev == NULL) {
        return false;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    // 新结点先记录左右邻居，再分别修正两侧结点的链接。
    node->prev = position->prev;
    node->next = position;
    position->prev->next = node;
    position->prev = node;
    return true;
}

// 删除指定数据结点，同时维护前后两个方向的链接。
bool Delete(Node *node, int *removed) {
    if (node == NULL || node->prev == NULL || node->next == NULL) {
        return false;
    }

    // 两条链接都要修改，漏掉任意一条都会破坏双向链表。
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (removed != NULL) {
        *removed = node->data;
    }
    free(node);
    return true;
}

// 从头哨兵向后遍历。
void PrintForward(const DoublyList *list) {
    for (const Node *p = list->head.next; p != &list->tail; p = p->next) {
        printf("%d%s", p->data, p->next == &list->tail ? "\n" : " <-> ");
    }
}

// 从尾哨兵向前遍历。
void PrintBackward(const DoublyList *list) {
    for (const Node *p = list->tail.prev; p != &list->head; p = p->prev) {
        printf("%d%s", p->data, p->prev == &list->head ? "\n" : " <-> ");
    }
}

// 释放所有数据结点，并恢复为空表状态。
void Clear(DoublyList *list) {
    Node *p = list->head.next;
    while (p != &list->tail) {
        Node *next = p->next;
        free(p);
        p = next;
    }
    Init(list);
}

int main(void) {
    DoublyList list;
    Init(&list);
    InsertBefore(&list.tail, 10);
    InsertBefore(&list.tail, 20);
    InsertBefore(&list.tail, 30);
    PrintForward(&list);
    PrintBackward(&list);

    int removed;
    Delete(list.head.next->next, &removed);
    printf("removed = %d\n", removed);
    PrintForward(&list);
    Clear(&list);
    return 0;
}
