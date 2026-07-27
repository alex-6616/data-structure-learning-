#include <stdbool.h>
#include <stdio.h>

#define LIST_CAPACITY 8

typedef int ElementType;

typedef struct {
    ElementType data[LIST_CAPACITY];
    int length;
} List;

void ListInit(List *list) {
    list->length = 0;
}

bool ListIsEmpty(const List *list) {
    return list->length == 0;
}

int ListLength(const List *list) {
    return list->length;
}

int ListFind(const List *list, ElementType value) {
    for (int i = 0; i < list->length; ++i) {
        if (list->data[i] == value) {
            return i;
        }
    }
    return -1;
}

bool ListInsert(List *list, int index, ElementType value) {
    if (index < 0 || index > list->length ||
        list->length == LIST_CAPACITY) {
        return false;
    }

    for (int i = list->length; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->length;
    return true;
}

bool ListDelete(List *list, int index, ElementType *removed) {
    if (index < 0 || index >= list->length) {
        return false;
    }

    if (removed != NULL) {
        *removed = list->data[index];
    }
    for (int i = index; i < list->length - 1; ++i) {
        list->data[i] = list->data[i + 1];
    }
    --list->length;
    return true;
}

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
