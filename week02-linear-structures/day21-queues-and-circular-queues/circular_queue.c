#include <stdbool.h>
#include <stdio.h>

#define QUEUE_CAPACITY 6

typedef struct {
    int data[QUEUE_CAPACITY];
    int front;
    int rear;
} CircularQueue;

void Init(CircularQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

bool IsEmpty(const CircularQueue *queue) {
    return queue->front == queue->rear;
}

bool IsFull(const CircularQueue *queue) {
    return (queue->rear + 1) % QUEUE_CAPACITY == queue->front;
}

int Size(const CircularQueue *queue) {
    return (queue->rear - queue->front + QUEUE_CAPACITY) %
           QUEUE_CAPACITY;
}

bool Enqueue(CircularQueue *queue, int value) {
    if (queue == NULL || IsFull(queue)) {
        return false;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    return true;
}

bool Dequeue(CircularQueue *queue, int *removed) {
    if (queue == NULL || IsEmpty(queue)) {
        return false;
    }
    if (removed != NULL) {
        *removed = queue->data[queue->front];
    }
    queue->front = (queue->front + 1) % QUEUE_CAPACITY;
    return true;
}

int main(void) {
    CircularQueue queue;
    Init(&queue);
    for (int value = 10; value <= 50; value += 10) {
        Enqueue(&queue, value);
    }

    int removed;
    Dequeue(&queue, &removed);
    Dequeue(&queue, &removed);
    Enqueue(&queue, 60);
    Enqueue(&queue, 70);

    printf("size = %d, front=%d, rear=%d\n",
           Size(&queue), queue.front, queue.rear);
    while (Dequeue(&queue, &removed)) {
        printf("%d ", removed);
    }
    putchar('\n');
    return 0;
}
