#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_EXPRESSION 256

int Precedence(char operator) {
    if (operator == '*' || operator == '/') {
        return 2;
    }
    if (operator == '+' || operator == '-') {
        return 1;
    }
    return 0;
}

bool AppendToken(char output[], int *length, const char *token, int token_length) {
    if (*length + token_length + 2 >= MAX_EXPRESSION) {
        return false;
    }
    for (int i = 0; i < token_length; ++i) {
        output[(*length)++] = token[i];
    }
    output[(*length)++] = ' ';
    output[*length] = '\0';
    return true;
}

bool Convert(const char *infix, char postfix[]) {
    char operators[MAX_EXPRESSION];
    int top = 0;
    int out = 0;
    postfix[0] = '\0';

    for (int i = 0; infix[i] != '\0';) {
        if (isspace((unsigned char)infix[i])) {
            ++i;
        } else if (isalnum((unsigned char)infix[i]) || infix[i] == '_') {
            int start = i;
            while (isalnum((unsigned char)infix[i]) || infix[i] == '_') {
                ++i;
            }
            if (!AppendToken(postfix, &out, infix + start, i - start)) {
                return false;
            }
        } else if (infix[i] == '(') {
            operators[top++] = infix[i++];
        } else if (infix[i] == ')') {
            while (top > 0 && operators[top - 1] != '(') {
                char operator = operators[--top];
                if (!AppendToken(postfix, &out, &operator, 1)) {
                    return false;
                }
            }
            if (top == 0) {
                return false;
            }
            --top;
            ++i;
        } else if (strchr("+-*/", infix[i]) != NULL) {
            char current = infix[i++];
            while (top > 0 && operators[top - 1] != '(' &&
                   Precedence(operators[top - 1]) >= Precedence(current)) {
                char operator = operators[--top];
                if (!AppendToken(postfix, &out, &operator, 1)) {
                    return false;
                }
            }
            operators[top++] = current;
        } else {
            return false;
        }
    }

    while (top > 0) {
        char operator = operators[--top];
        if (operator == '(') {
            return false;
        }
        if (!AppendToken(postfix, &out, &operator, 1)) {
            return false;
        }
    }
    if (out > 0) {
        postfix[out - 1] = '\0';
    }
    return true;
}

int main(void) {
    const char *tests[] = {
        "A + B * C",
        "(A + B) * C",
        "12 + 3 * (4 - 2)"
    };
    char postfix[MAX_EXPRESSION];

    for (int i = 0; i < 3; ++i) {
        if (Convert(tests[i], postfix)) {
            printf("%s  =>  %s\n", tests[i], postfix);
        } else {
            printf("%s  =>  invalid\n", tests[i]);
        }
    }
    return 0;
}
