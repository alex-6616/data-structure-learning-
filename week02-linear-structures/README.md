# Week 2–3: Linear Structures

> 对应阶段：第 2–3 阶段  
> 对应进度：Day 8–22  
> 主题：线性表、链表、栈与队列

本目录按每天的学习内容组织。每个 Day 文件夹包含：

- `notes.md`：当天概念、ASCII 过程图、复杂度、易错点与掌握检查；
- `*.c`：可独立编译运行的 C11 示例；
- 少数复盘日会用综合练习代替新数据结构实现。

## 目录

| Day | 文件夹 | 主要代码 |
|---|---|---|
| 08 | [`day08-adt-and-linear-lists`](day08-adt-and-linear-lists/) | `list_adt_demo.c` |
| 09 | [`day09-array-list`](day09-array-list/) | `static_array_list.c`, `dynamic_array_list.c` |
| 10 | [`day10-singly-linked-list-basics`](day10-singly-linked-list-basics/) | `create_and_traverse.c` |
| 11 | [`day11-linked-list-insertion-and-deletion`](day11-linked-list-insertion-and-deletion/) | `insert_delete.c` |
| 12 | [`day12-classic-linked-list-problems`](day12-classic-linked-list-problems/) | `reverse_list.c`, `merge_sorted_lists.c` |
| 13 | [`day13-doubly-and-circular-linked-lists`](day13-doubly-and-circular-linked-lists/) | `doubly_linked_list.c`, `circular_linked_list.c` |
| 14 | [`day14-polynomial-representation`](day14-polynomial-representation/) | `polynomial_addition.c` |
| 15 | [`day15-linear-list-review`](day15-linear-list-review/) | `linear_list_review.c` |
| 16 | [`day16-stack-basics`](day16-stack-basics/) | `array_stack.c` |
| 17 | [`day17-linked-stack`](day17-linked-stack/) | `linked_stack.c` |
| 18 | [`day18-parentheses-matching`](day18-parentheses-matching/) | `parentheses_matching.c` |
| 19 | [`day19-postfix-expression-evaluation`](day19-postfix-expression-evaluation/) | `postfix_evaluation.c` |
| 20 | [`day20-infix-to-postfix-conversion`](day20-infix-to-postfix-conversion/) | `infix_to_postfix.c` |
| 21 | [`day21-queues-and-circular-queues`](day21-queues-and-circular-queues/) | `circular_queue.c`, `linked_queue.c` |
| 22 | [`day22-queue-applications`](day22-queue-applications/) | `service_queue.c`, `bfs_demo.c` |

## 编译

单个文件：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic file.c -o program
./program
```

开启 AddressSanitizer 检查越界和内存错误：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -fsanitize=address file.c -o program
```

## 使用方式

1. 先读当天 `notes.md`，自己复述概念并手画过程图；
2. 不看答案，脱稿写一遍核心操作；
3. 对照 `.c` 示例修改；
4. 补充空结构、单元素、首尾位置和容量边界测试；
5. 完成当天 `notes.md` 末尾的掌握检查。

该目录只是重新组织 GitHub 文件，不改变原 60 天学习计划。
