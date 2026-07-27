#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_EXPRESSION 256

// 返回运算符优先级，数值越大表示优先级越高。
int Precedence(char operator) {
    if (operator == '*' || operator == '/') {
        return 2;
    }
    if (operator == '+' || operator == '-') {
        return 1;
    }
    return 0;
}

// 将一个记号和分隔空格安全地追加到输出字符串。
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

// 使用运算符栈将中缀表达式转换为后缀表达式。
bool Convert(const char *infix, char postfix[]) {
    char operators[MAX_EXPRESSION];
    int top = 0;
    int out = 0;
    postfix[0] = '\0';

    for (int i = 0; infix[i] != '\0';) {
        if (isspace((unsigned char)infix[i])) {
            ++i;
        } else if (isalnum((unsigned char)infix[i]) || infix[i] == '_') {
            // 连续字母、数字或下划线组成一个完整操作数。
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
            // 右括号不输出；弹出运算符直到遇到对应左括号。
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
            // 栈顶优先级不低于当前运算符时先弹栈，保证左结合。
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

    // 扫描结束后，将剩余运算符依次输出。
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
