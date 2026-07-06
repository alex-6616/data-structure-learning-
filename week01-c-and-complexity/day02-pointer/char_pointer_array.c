#include <stdio.h>

int main() {
    char *names[] = {"Tom", "Jack", "Alice"};
    char **p = names;

    printf("%s %c\n", *p, **p);

    p++;
    printf("%s %c\n", *p, **p);

    p++;
    printf("%s %c\n", *p, **p);

    return 0;
}

/*输出：
  Tom T
  Jack J
  Alice A
*/
