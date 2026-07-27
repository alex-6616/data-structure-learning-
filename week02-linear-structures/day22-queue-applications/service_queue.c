#include <stdbool.h>
#include <stdio.h>

#define CAPACITY 16

typedef struct {
    char name;
    int arrival;
    int service_time;
} Customer;

typedef struct {
    Customer data[CAPACITY];
    int front;
    int rear;
} Queue;

// 初始化循环等待队列。
void Init(Queue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

// front 与 rear 相等时队列为空。
bool IsEmpty(const Queue *queue) {
    return queue->front == queue->rear;
}

// 将顾客加入队尾；预留一个空位用于区分队空和队满。
bool Enqueue(Queue *queue, Customer customer) {
    int next = (queue->rear + 1) % CAPACITY;
    if (next == queue->front) {
        return false;
    }
    queue->data[queue->rear] = customer;
    queue->rear = next;
    return true;
}

// 让队头顾客出队。
bool Dequeue(Queue *queue, Customer *customer) {
    if (IsEmpty(queue)) {
        return false;
    }
    *customer = queue->data[queue->front];
    queue->front = (queue->front + 1) % CAPACITY;
    return true;
}

int main(void) {
    const Customer arrivals[] = {
        {'A', 0, 3}, {'B', 1, 2}, {'C', 1, 1}, {'D', 4, 2}
    };
    const int count = (int)(sizeof(arrivals) / sizeof(arrivals[0]));
    Queue waiting;
    Init(&waiting);

    int next_arrival = 0;
    int clock = 0;
    while (next_arrival < count || !IsEmpty(&waiting)) {
        // 先将当前时刻前已经到达的顾客全部加入等待队列。
        while (next_arrival < count &&
               arrivals[next_arrival].arrival <= clock) {
            Enqueue(&waiting, arrivals[next_arrival]);
            printf("time %d: %c arrives\n",
                   arrivals[next_arrival].arrival,
                   arrivals[next_arrival].name);
            ++next_arrival;
        }

        Customer current;
        if (Dequeue(&waiting, &current)) {
            // 服务期间时钟直接推进相应的服务时长。
            printf("time %d: serve %c, wait %d\n",
                   clock, current.name, clock - current.arrival);
            clock += current.service_time;
        } else {
            // 无人等待时，直接跳到下一位顾客的到达时刻。
            clock = arrivals[next_arrival].arrival;
        }
    }
    return 0;
}
