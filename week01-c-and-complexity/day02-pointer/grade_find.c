#include <stdio.h>

struct Student {
    int id;
    int score;
};

int main() {
    int n;
    struct Student stu[100];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &stu[i].id, &stu[i].score);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (stu[j].score < stu[j + 1].score) {
                struct Student temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }//冒泡

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", stu[i].id, stu[i].score);
    }

    return 0;
}
