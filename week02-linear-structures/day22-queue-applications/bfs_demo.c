#include <stdbool.h>
#include <stdio.h>

#define VERTICES 6

typedef struct {
    int data[VERTICES];
    int front;
    int rear;
} Queue;

void Enqueue(Queue *queue, int vertex) {
    queue->data[queue->rear++] = vertex;
}

int Dequeue(Queue *queue) {
    return queue->data[queue->front++];
}

bool IsEmpty(const Queue *queue) {
    return queue->front == queue->rear;
}

void BFS(const int graph[VERTICES][VERTICES], int start) {
    bool visited[VERTICES] = {false};
    Queue queue = {{0}, 0, 0};

    visited[start] = true;
    Enqueue(&queue, start);

    while (!IsEmpty(&queue)) {
        int vertex = Dequeue(&queue);
        printf("%c ", 'A' + vertex);

        for (int neighbor = 0; neighbor < VERTICES; ++neighbor) {
            if (graph[vertex][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                Enqueue(&queue, neighbor);
            }
        }
    }
    putchar('\n');
}

int main(void) {
    const int graph[VERTICES][VERTICES] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0}
    };

    printf("BFS from A: ");
    BFS(graph, 0);
    return 0;
}
