# Day 10: Singly Linked List Basics

> 学习阶段：第 2 阶段｜链表  
> 对应章节：Ch3.2 单链表基础  
> 今日目标：分清结点、头指针、头结点和首元结点

## 1. 结点

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;
```

`Node *p` 指向整个结点，而不是只指向数据域：

```text
p ─────▶ +----------------+
         | data |  next   |
         +----------------+
          p->data  p->next
```

## 2. 带头结点与不带头结点

不带头结点：

```text
head ──▶ [12|next] ──▶ [25|NULL]
         首元结点
```

带头结点：

```text
head ──▶ [dummy|next] ──▶ [12|next] ──▶ [25|NULL]
         头结点           首元结点
```

头结点不保存有效元素，它让空表和表头操作更统一。

## 3. 尾插法建表

```text
初始：
head, tail
     │
     ▼
 [dummy|NULL]

插入 12：
head ──▶ [dummy|next] ──▶ [12|NULL]
                              ▲
                             tail

插入 25：
head ──▶ [dummy|next] ──▶ [12|next] ──▶ [25|NULL]
                                            ▲
                                           tail
```

保持 `tail` 后，每次尾插是 `O(1)`；如果每次都从头寻找尾结点，建立 `n` 个结点会退化为 `O(n²)`。

## 4. 遍历与销毁

遍历时当前指针沿 `next` 移动；销毁时必须先保存后继，再释放当前结点：

```text
current       next
   │            │
   ▼            ▼
 [A|next] ──▶ [B|next] ──▶ ...

先 next = current->next
再 free(current)
最后 current = next
```

## 5. 今日代码

`create_and_traverse.c`：尾插建表、遍历、查找、统计长度和销毁。

## 6. 掌握检查

- [ ] 能解释 `typedef struct Node ... Node;`；
- [ ] 能区分头指针、头结点和首元结点；
- [ ] 能画出尾插时 `tail` 的变化；
- [ ] 能解释链表结点为什么不要求地址连续；
- [ ] 能脱稿写出遍历和销毁。

### 知识遗漏检查

今日已覆盖单链表的定义、入口、建表、遍历和释放。插入与删除的指针修改放在 Day 11。
