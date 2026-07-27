#include <stdbool.h>
#include <stdio.h>

#define VERTICES 6

typedef struct {
    int data[VERTICES];
    int front;
    int rear;
} Queue;

// 将待访问顶点加入队尾。
void Enqueue(Queue *queue, int vertex) {
    queue->data[queue->rear++] = vertex;
}

// 取出并返回队头顶点。
int Dequeue(Queue *queue) {
    return queue->data[queue->front++];
}

// 判断辅助队列是否为空。
bool IsEmpty(const Queue *queue) {
    return queue->front == queue->rear;
}

// 从 start 顶点开始进行广度优先遍历。
void BFS(const int graph[VERTICES][VERTICES], int start) {
    bool visited[VERTICES] = {false};
    Queue queue = {{0}, 0, 0};

    // 顶点入队时立刻标记，避免它被其他相邻顶点重复入队。
    visited[start] = true;
    Enqueue(&queue, start);

    while (!IsEmpty(&queue)) {
        int vertex = Dequeue(&queue);
        printf("%c ", 'A' + vertex);

        // 检查当前顶点的所有邻接点，将未访问者依次入队。
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
