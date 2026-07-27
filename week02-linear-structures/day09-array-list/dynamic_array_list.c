#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
    int capacity;
} DynamicList;

// 分配初始存储空间并建立空的动态顺序表。
bool Init(DynamicList *list, int initial_capacity) {
    if (list == NULL || initial_capacity <= 0) {
        return false;
    }
    list->data = malloc((size_t)initial_capacity * sizeof(int));
    if (list->data == NULL) {
        return false;
    }
    list->length = 0;
    list->capacity = initial_capacity;
    return true;
}

// 将容量扩展到 new_capacity；容量足够时无需重新分配。
bool Reserve(DynamicList *list, int new_capacity) {
    if (new_capacity <= list->capacity) {
        return true;
    }

    // 先用临时指针接收 realloc，失败时原内存仍然有效。
    int *new_data =
        realloc(list->data, (size_t)new_capacity * sizeof(int));
    if (new_data == NULL) {
        return false;
    }
    list->data = new_data;
    list->capacity = new_capacity;
    return true;
}

// 在指定下标插入元素，空间不足时容量翻倍。
bool Insert(DynamicList *list, int index, int value) {
    if (list == NULL || index < 0 || index > list->length) {
        return false;
    }
    if (list->length == list->capacity &&
        !Reserve(list, list->capacity * 2)) {
        return false;
    }

    // 插入时从后向前移动，避免覆盖原有元素。
    for (int i = list->length; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->length;
    return true;
}

// 释放动态数组，并将各字段重置，避免留下悬空指针。
void Destroy(DynamicList *list) {
    free(list->data);
    list->data = NULL;
    list->length = 0;
    list->capacity = 0;
}

int main(void) {
    DynamicList list;
    if (!Init(&list, 2)) {
        return EXIT_FAILURE;
    }

    for (int value = 10; value <= 50; value += 10) {
        if (!Insert(&list, list.length, value)) {
            Destroy(&list);
            return EXIT_FAILURE;
        }
        printf("insert %d: length=%d capacity=%d\n",
               value, list.length, list.capacity);
    }

    Destroy(&list);
    return EXIT_SUCCESS;
}
