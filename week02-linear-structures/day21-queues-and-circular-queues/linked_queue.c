#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} LinkedQueue;

// 创建头结点，并让 front、rear 同时指向它表示空队列。
bool Init(LinkedQueue *queue) {
    Node *dummy = malloc(sizeof(Node));
    if (dummy == NULL) {
        return false;
    }
    dummy->next = NULL;
    queue->front = dummy;
    queue->rear = dummy;
    return true;
}

// front 与 rear 指向同一头结点时队列为空。
bool IsEmpty(const LinkedQueue *queue) {
    return queue->front == queue->rear;
}

// 在链表尾部添加结点并更新 rear。
bool Enqueue(LinkedQueue *queue, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    return true;
}

// 删除队头的第一个数据结点。
bool Dequeue(LinkedQueue *queue, int *removed) {
    if (IsEmpty(queue)) {
        return false;
    }
    Node *target = queue->front->next;
    queue->front->next = target->next;
    // 删除最后一个数据结点后，rear 必须重新指回头结点。
    if (queue->rear == target) {
        queue->rear = queue->front;
    }
    if (removed != NULL) {
        *removed = target->data;
    }
    free(target);
    return true;
}

// 清空所有数据结点，再释放头结点。
void Destroy(LinkedQueue *queue) {
    int ignored;
    while (Dequeue(queue, &ignored)) {
    }
    free(queue->front);
    queue->front = NULL;
    queue->rear = NULL;
}

int main(void) {
    LinkedQueue queue;
    if (!Init(&queue)) {
        return EXIT_FAILURE;
    }

    Enqueue(&queue, 10);
    Enqueue(&queue, 20);
    Enqueue(&queue, 30);
    int value;
    while (Dequeue(&queue, &value)) {
        printf("dequeue %d\n", value);
    }
    printf("front == rear: %s\n",
           queue.front == queue.rear ? "yes" : "no");
    Destroy(&queue);
    return EXIT_SUCCESS;
}
