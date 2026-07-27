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

void Init(Queue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

bool IsEmpty(const Queue *queue) {
    return queue->front == queue->rear;
}

bool Enqueue(Queue *queue, Customer customer) {
    int next = (queue->rear + 1) % CAPACITY;
    if (next == queue->front) {
        return false;
    }
    queue->data[queue->rear] = customer;
    queue->rear = next;
    return true;
}

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
            printf("time %d: serve %c, wait %d\n",
                   clock, current.name, clock - current.arrival);
            clock += current.service_time;
        } else {
            clock = arrivals[next_arrival].arrival;
        }
    }
    return 0;
}
