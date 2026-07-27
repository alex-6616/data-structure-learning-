#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_EXPRESSION 256

typedef struct {
    char bracket;
    int position;
} Entry;

bool IsLeft(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

bool IsRight(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

bool Matches(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

bool Check(const char *expression) {
    Entry stack[MAX_EXPRESSION];
    int top = 0;

    for (int i = 0; expression[i] != '\0'; ++i) {
        char ch = expression[i];
        if (IsLeft(ch)) {
            stack[top++] = (Entry){ch, i};
        } else if (IsRight(ch)) {
            if (top == 0) {
                printf("position %d: '%c' has no left bracket\n", i, ch);
                return false;
            }
            Entry left = stack[--top];
            if (!Matches(left.bracket, ch)) {
                printf("position %d: '%c' does not match '%c' at %d\n",
                       i, ch, left.bracket, left.position);
                return false;
            }
        }
    }

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
