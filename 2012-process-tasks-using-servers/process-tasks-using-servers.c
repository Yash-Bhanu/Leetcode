#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long key;
    int id;       
} Node;

static inline bool less(Node a, Node b) {
    return a.key != b.key ? a.key < b.key : a.id < b.id;
}

void push(Node* heap, int* size, long long key, int id) {
    int i = (*size)++;
    heap[i] = (Node){key, id};
    while (i > 0) {
        int p = (i - 1) / 2;
        if (less(heap[p], heap[i])) break;
        Node tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

Node pop(Node* heap, int* size) {
    Node top = heap[0];
    heap[0] = heap[--(*size)];
    int i = 0;
    while (i * 2 + 1 < *size) {
        int child = i * 2 + 1;
        if (child + 1 < *size && less(heap[child + 1], heap[child])) {
            child++;
        }
        if (less(heap[i], heap[child])) break;
        Node tmp = heap[i];
        heap[i] = heap[child];
        heap[child] = tmp;
        i = child;
    }
    return top;
}

int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    Node* freeHeap = (Node*)malloc(sizeof(Node) * serversSize);
    Node* busyHeap = (Node*)malloc(sizeof(Node) * serversSize);
    int freeSize = 0, busySize = 0;

    for (int i = 0; i < serversSize; i++) {
        push(freeHeap, &freeSize, servers[i], i);
    }

    int* ans = (int*)malloc(sizeof(int) * tasksSize);
    *returnSize = tasksSize;
    long long time = 0;

    for (int j = 0; j < tasksSize; j++) {
        if (time < j) {
            time = j;
        }
        if (freeSize == 0 && busyHeap[0].key > time) {
            time = busyHeap[0].key;
        }
        while (busySize > 0 && busyHeap[0].key <= time) {
            Node s = pop(busyHeap, &busySize);
            push(freeHeap, &freeSize, servers[s.id], s.id);
        }
        Node assigned = pop(freeHeap, &freeSize);
        ans[j] = assigned.id;
        push(busyHeap, &busySize, time + tasks[j], assigned.id);
    }

    free(freeHeap);
    free(busyHeap);
    return ans;
}