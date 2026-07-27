#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 8

typedef struct {
    int data[CAPACITY];
    int length;
} ArrayList;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 顺序表插入：需要移动 index 之后的所有元素。
bool ArrayInsert(ArrayList *list, int index, int value) {
    if (index < 0 || index > list->length || list->length == CAPACITY) {
        return false;
    }
    // 从后向前移动，避免数据被覆盖。
    for (int i = list->length; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->length;
    return true;
}

// 单链表后插：已知结点位置时只需修改两个指针。
bool ListInsertAfter(Node *position, int value) {
    if (position == NULL) {
        return false;
    }
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    // 先接后继，再让 position 指向新结点。
    node->next = position->next;
    position->next = node;
    return true;
}

// 释放链表所有结点，包括头结点。
void ListDestroy(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    ArrayList array = {{0}, 0};
    ArrayInsert(&array, 0, 10);
    ArrayInsert(&array, 1, 30);
    ArrayInsert(&array, 1, 20);

    Node *head = malloc(sizeof(Node));
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    head->next = NULL;
    ListInsertAfter(head, 30);
    ListInsertAfter(head, 20);
    ListInsertAfter(head, 10);

    printf("array access data[1] = %d\n", array.data[1]);
    printf("linked traversal: ");
    for (Node *p = head->next; p != NULL; p = p->next) {
        printf("%d%s", p->data, p->next == NULL ? "\n" : " -> ");
    }

    ListDestroy(head);
    return EXIT_SUCCESS;
}
