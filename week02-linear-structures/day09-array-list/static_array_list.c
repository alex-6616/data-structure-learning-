#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 6

typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// 初始化静态顺序表。
void Init(SeqList *list) {
    list->length = 0;
}

// 在 index 位置插入元素，index 可以等于 length（尾插）。
bool Insert(SeqList *list, int index, int value) {
    if (list == NULL || index < 0 || index > list->length ||
        list->length == MAX_SIZE) {
        return false;
    }

    // 从后向前右移，为新元素腾出位置。
    for (int i = list->length; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->length;
    return true;
}

// 删除 index 位置的元素，并可通过 removed 返回其值。
bool Delete(SeqList *list, int index, int *removed) {
    if (list == NULL || index < 0 || index >= list->length) {
        return false;
    }

    if (removed != NULL) {
        *removed = list->data[index];
    }
    // 从删除位置开始向前覆盖，逻辑长度最后减一。
    for (int i = index; i < list->length - 1; ++i) {
        list->data[i] = list->data[i + 1];
    }
    --list->length;
    return true;
}

// 顺序查找目标值，未找到时返回 -1。
int Find(const SeqList *list, int value) {
    for (int i = 0; i < list->length; ++i) {
        if (list->data[i] == value) {
            return i;
        }
    }
    return -1;
}

// 输出所有有效元素，不访问 length 之后的未使用空间。
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
