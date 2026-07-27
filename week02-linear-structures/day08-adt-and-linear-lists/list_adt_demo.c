#include <stdbool.h>
#include <stdio.h>

#define LIST_CAPACITY 8

typedef int ElementType;

typedef struct {
    ElementType data[LIST_CAPACITY];
    int length;
} List;

// 初始化线性表，使其成为空表。
void ListInit(List *list) {
    list->length = 0;
}

// 判断线性表是否为空。
bool ListIsEmpty(const List *list) {
    return list->length == 0;
}

// 返回线性表当前的有效元素个数。
int ListLength(const List *list) {
    return list->length;
}

// 按值查找元素，成功返回下标，失败返回 -1。
int ListFind(const List *list, ElementType value) {
    for (int i = 0; i < list->length; ++i) {
        if (list->data[i] == value) {
            return i;
        }
    }
    return -1;
}

// 在 index 位置插入元素，合法范围是 [0, length]。
bool ListInsert(List *list, int index, ElementType value) {
    if (index < 0 || index > list->length ||
        list->length == LIST_CAPACITY) {
        return false;
    }

    // 必须从后向前移动，否则尚未搬走的元素会被覆盖。
    for (int i = list->length; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->length;
    return true;
}

// 删除 index 位置的元素，并通过 removed 可选地返回被删值。
bool ListDelete(List *list, int index, ElementType *removed) {
    if (index < 0 || index >= list->length) {
        return false;
    }

    if (removed != NULL) {
        *removed = list->data[index];
    }
    // 删除后将后续元素依次左移，填补空位。
    for (int i = index; i < list->length - 1; ++i) {
        list->data[i] = list->data[i + 1];
    }
    --list->length;
    return true;
}

// 按逻辑顺序输出线性表中的有效元素。
void ListPrint(const List *list) {
    printf("[");
    for (int i = 0; i < list->length; ++i) {
        printf("%s%d", i == 0 ? "" : ", ", list->data[i]);
    }
    printf("]\n");
}

int main(void) {
    List numbers;
    ListInit(&numbers);

    ListInsert(&numbers, 0, 10);
    ListInsert(&numbers, 1, 30);
    ListInsert(&numbers, 1, 20);
    ListPrint(&numbers);

    printf("length = %d, find 20 = %d\n",
           ListLength(&numbers), ListFind(&numbers, 20));

    int removed;
    if (ListDelete(&numbers, 1, &removed)) {
        printf("removed %d\n", removed);
    }
    ListPrint(&numbers);
    printf("is empty: %s\n", ListIsEmpty(&numbers) ? "yes" : "no");
    return 0;
}
