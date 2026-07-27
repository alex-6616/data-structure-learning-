#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term *next;
} Term;

// 将一个非零项追加到多项式尾部；零系数项直接忽略。
int Append(Term **tail, int coefficient, int exponent) {
    if (coefficient == 0) {
        return 1;
    }
    Term *term = malloc(sizeof(Term));
    if (term == NULL) {
        return 0;
    }
    term->coefficient = coefficient;
    term->exponent = exponent;
    term->next = NULL;
    (*tail)->next = term;
    *tail = term;
    return 1;
}

// 根据已按指数降序排列的数组创建多项式链表。
Term *Create(const int coefficients[], const int exponents[], int count) {
    Term dummy = {0, 0, NULL};
    Term *tail = &dummy;

    for (int i = 0; i < count; ++i) {
        if (!Append(&tail, coefficients[i], exponents[i])) {
            Term *p = dummy.next;
            while (p != NULL) {
                Term *next = p->next;
                free(p);
                p = next;
            }
            return NULL;
        }
    }
    return dummy.next;
}

// 合并两个降幂排列的多项式，返回新建的结果链表。
Term *Add(const Term *left, const Term *right) {
    Term dummy = {0, 0, NULL};
    Term *tail = &dummy;

    while (left != NULL || right != NULL) {
        int coefficient;
        int exponent;

        // 指数较大的项先进入结果；指数相同则合并系数。
        if (right == NULL ||
            (left != NULL && left->exponent > right->exponent)) {
            coefficient = left->coefficient;
            exponent = left->exponent;
            left = left->next;
        } else if (left == NULL || right->exponent > left->exponent) {
            coefficient = right->coefficient;
            exponent = right->exponent;
            right = right->next;
        } else {
            coefficient = left->coefficient + right->coefficient;
            exponent = left->exponent;
            left = left->next;
            right = right->next;
        }

        // Append 会自动跳过相加后系数为 0 的项。
        if (!Append(&tail, coefficient, exponent)) {
            Term *p = dummy.next;
            while (p != NULL) {
                Term *next = p->next;
                free(p);
                p = next;
            }
            return NULL;
        }
    }
    return dummy.next;
}

// 按“系数 + 指数”的形式输出多项式。
void Print(const Term *polynomial) {
    if (polynomial == NULL) {
        puts("0");
        return;
    }
    for (const Term *p = polynomial; p != NULL; p = p->next) {
        printf("(%+d)x^%d%s", p->coefficient, p->exponent,
               p->next == NULL ? "\n" : " ");
    }
}

// 释放多项式的全部项结点。
void Destroy(Term *polynomial) {
    while (polynomial != NULL) {
        Term *next = polynomial->next;
        free(polynomial);
        polynomial = next;
    }
}

int main(void) {
    const int p_coef[] = {5, 3, -2};
    const int p_exp[] = {8, 3, 0};
    const int q_coef[] = {2, 4, 2};
    const int q_exp[] = {8, 2, 0};

    Term *p = Create(p_coef, p_exp, 3);
    Term *q = Create(q_coef, q_exp, 3);
    Term *sum = Add(p, q);
    Print(p);
    Print(q);
    Print(sum);

    Destroy(p);
    Destroy(q);
    Destroy(sum);
    return 0;
}
