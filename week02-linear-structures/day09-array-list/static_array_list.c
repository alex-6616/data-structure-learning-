#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 6

typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

void Init(SeqList *list) {
    list->length = 0;
}

bool Insert(SeqList *list, int index, int value) {
    if (list == NULL || index < 0 || index > list->length ||
        list->length == MAX_SIZE) {
        return false;
    }

    for (int i = list->length; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->length;
    return true;
}

bool Delete(SeqList *list, int index, int *removed) {
    if (list == NULL || index < 0 || index >= list->length) {
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

int Find(const SeqList *list, int value) {
    for (int i = 0; i < list->length; ++i) {
        if (list->data[i] == value) {
            return i;
        }
    }
    return -1;
}

void Print(const SeqList *list) {
    for (int i = 0; i < list->length; ++i) {
        printf("%d%c", list->data[i],
               i + 1 == list->length ? '\n' : ' ');
    }
}

int main(void) {
    SeqList list;
    Init(&list);

    Insert(&list, 0, 12);
    Insert(&list, 1, 25);
    Insert(&list, 2, 37);
    Insert(&list, 1, 20);
    Print(&list);

    int removed;
    Delete(&list, 1, &removed);
    printf("removed = %d, index of 37 = %d\n", removed, Find(&list, 37));
    Print(&list);
    return 0;
}
