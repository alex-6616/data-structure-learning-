#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define STACK_CAPACITY 64

bool Apply(int left, int right, char operator, int *result) {
    switch (operator) {
        case '+': *result = left + right; return true;
        case '-': *result = left - right; return true;
        case '*': *result = left * right; return true;
        case '/':
            if (right == 0) {
                return false;
            }
            *result = left / right;
            return true;
        default:
            return false;
    }
}

bool ParseInteger(const char *token, int *value) {
    char *end;
    errno = 0;
    long parsed = strtol(token, &end, 10);
    if (errno != 0 || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return false;
    }
    *value = (int)parsed;
    return true;
}

bool Evaluate(char *expression, int *answer) {
    int stack[STACK_CAPACITY];
    int top = 0;

    for (char *token = strtok(expression, " \t\r\n");
         token != NULL;
         token = strtok(NULL, " \t\r\n")) {
        int value;
        if (ParseInteger(token, &value)) {
            if (top == STACK_CAPACITY) {
                return false;
            }
            stack[top++] = value;
        } else if (strlen(token) == 1 &&
                   strchr("+-*/", token[0]) != NULL) {
            if (top < 2) {
                return false;
            }
            int right = stack[--top];
            int left = stack[--top];
            if (!Apply(left, right, token[0], &value)) {
                return false;
            }
            stack[top++] = value;
        } else {
            return false;
        }
    }

    if (top != 1) {
        return false;
    }
    *answer = stack[0];
    return true;
}

int main(void) {
    char expression[MAX_LINE] = "3 4 + 2 *";
    int answer;

    if (Evaluate(expression, &answer)) {
        printf("result = %d\n", answer);
    } else {
        puts("invalid postfix expression");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
