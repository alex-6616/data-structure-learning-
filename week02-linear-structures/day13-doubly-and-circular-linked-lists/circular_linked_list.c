#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 创建带头结点的空循环链表，空表时 head->next 指回 head。
Node *CreateEmpty(void) {
    Node *head = malloc(sizeof(Node));
    if (head != NULL) {
        head->next = head;
    }
    return head;
}

// 在循环链表尾部插入新结点。
bool PushBack(Node *head, int value) {
    if (head == NULL) {
        return false;
    }

    Node *tail = head;
    // 循环链表没有 NULL，遇到 head 才表示绕回起点。
    while (tail->next != head) {
        tail = tail->next;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->next = head;  // 新尾结点必须重新指向头结点，保持成环。
    tail->next = node;
    return true;
}

// 从首个数据结点出发，只遍历一圈。
void PrintOnce(const Node *head) {
    const Node *p = head->next;
    while (p != head) {
        printf("%d%s", p->data, p->next == head ? "\n" : " -> ");
        p = p->next;
    }
}

// 先释放所有数据结点，最后释放头结点。
void Destroy(Node *head) {
    if (head == NULL) {
        return;
    }
    Node *p = head->next;
    while (p != head) {
        // 保存后继后再释放，且终止条件不能写成 p != NULL。
        Node *next = p->next;
        free(p);
        p = next;
    }
    free(head);
}

int main(void) {
    Node *head = CreateEmpty();
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    PushBack(head, 10);
    PushBack(head, 20);
    PushBack(head, 30);
    PrintOnce(head);
    Destroy(head);
    return EXIT_SUCCESS;
}
