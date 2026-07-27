#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_EXPRESSION 256

typedef struct {
    char bracket;
    int position;
} Entry;

// 判断字符是否为左括号。
bool IsLeft(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

// 判断字符是否为右括号。
bool IsRight(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

// 判断一对左右括号的类型是否匹配。
bool Matches(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

// 使用栈检查表达式中的括号是否正确配对。
bool Check(const char *expression) {
    Entry stack[MAX_EXPRESSION];
    int top = 0;

    for (int i = 0; expression[i] != '\0'; ++i) {
        char ch = expression[i];
        if (IsLeft(ch)) {
            // 左括号入栈，同时保存位置，便于报告错误。
            stack[top++] = (Entry){ch, i};
        } else if (IsRight(ch)) {
            if (top == 0) {
                printf("position %d: '%c' has no left bracket\n", i, ch);
                return false;
            }
            // 右括号应与最近出现且尚未匹配的左括号配对。
            Entry left = stack[--top];
            if (!Matches(left.bracket, ch)) {
                printf("position %d: '%c' does not match '%c' at %d\n",
                       i, ch, left.bracket, left.position);
                return false;
            }
        }
    }

    // 扫描结束后栈非空，说明仍有左括号未闭合。
    if (top != 0) {
        Entry left = stack[top - 1];
        printf("position %d: '%c' is not closed\n",
               left.position, left.bracket);
        return false;
    }
    return true;
}

int main(void) {
    const char *tests[] = {
        "([{}])",
        "a + (b * c)",
        "([)]",
        "(()",
        "())"
    };

    const int count = (int)(sizeof(tests) / sizeof(tests[0]));
    for (int i = 0; i < count; ++i) {
        printf("%-16s %s\n", tests[i], Check(tests[i]) ? "valid" : "invalid");
    }
    return 0;
}
