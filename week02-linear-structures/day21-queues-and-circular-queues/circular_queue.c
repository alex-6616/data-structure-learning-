#include <stdbool.h>
#include <stdio.h>

#define QUEUE_CAPACITY 6

typedef struct {
    int data[QUEUE_CAPACITY];
    int front;
    int rear;
} CircularQueue;

// 初始化空队列；front 指向队头元素，rear 指向下一可写位置。
void Init(CircularQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

// front 与 rear 重合时队列为空。
bool IsEmpty(const CircularQueue *queue) {
    return queue->front == queue->rear;
}

// 预留一个数组位置，用“rear 的下一格等于 front”表示队满。
bool IsFull(const CircularQueue *queue) {
    return (queue->rear + 1) % QUEUE_CAPACITY == queue->front;
}

// 计算循环队列中的实际元素个数。
int Size(const CircularQueue *queue) {
    // 加上容量再取模，可处理 rear 已绕到 front 前面的情况。
    return (queue->rear - queue->front + QUEUE_CAPACITY) %
           QUEUE_CAPACITY;
}

// 在队尾入队。
bool Enqueue(CircularQueue *queue, int value) {
    if (queue == NULL || IsFull(queue)) {
        return false;
    }
    queue->data[queue->rear] = value;
    // 取模使 rear 到达数组末尾后回到 0。
    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    return true;
}

// 从队头出队，并可返回被删除的元素。
bool Dequeue(CircularQueue *queue, int *removed) {
    if (queue == NULL || IsEmpty(queue)) {
        return false;
    }
    // front 当前指向队头，因此先读取元素，再移动 front。
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
