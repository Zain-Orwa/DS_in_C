````md
# 🧠 Peer Explanation — Linked Lists (Insert at Head & Tail)

## 🎯 Goal of this lesson
You learned your **first real linked list operations**:
- How a linked list is built from **nodes** connected by pointers
- How to **insert at the head** (front)
- How to **insert at the tail** (end)
- Why “losing the pointer” breaks the list (your bug)

---

## 📦 What is a Linked List (in C)?
A **linked list** is a chain of nodes.

Each node contains:
1) **data** (here: `value`)
2) a pointer to the **next** node (`next`)

```c
typedef struct node {
	int value;
	struct node *next;
} Node;
````

### ✅ Key idea

The list is identified by **one pointer**:

* `Node *head;`

That pointer stores the address of the **first node**.
If `head == NULL`, the list is empty.

---

## 🧠 Memory layout (Stack vs Heap)

### In `main`

```c
Node *list1_head = NULL;
```

* `list1_head` is a variable stored on the **stack**
* the nodes created by `calloc` are stored on the **heap**

### Diagram: where things live

```
STACK (main)                         HEAP (calloc)
+------------------+                 +------------------+
| list1_head       |   ----->        | Node { value, next }
| (pointer)        |                 | ... many nodes ... |
+------------------+                 +------------------+
```

So:

* stack holds the pointer
* heap holds the actual linked list nodes

---

## 🔗 Insert at Head (your lesson #1)

### ✅ What "insert at head" means

You want the new node to become the **first** element.

That means:

1. new node should point to the old head
2. return the new node as the new head

### Correct logic

```c
Node *insert_at_head(Node *head, int new_value)
{
	Node *new_node;

	new_node = calloc(1, sizeof(Node));
	if (!new_node)
		return (head);

	new_node->value = new_value;
	new_node->next = head;      // ⭐ link new node to old head
	return (new_node);          // ⭐ new node becomes head
}
```

### Why your old code failed

You wrote something like:

```c
new_node = head;
return (new_node);
```

That line does this:

✅ It does NOT link nodes
❌ It *throws away* the new node pointer and returns the old head again

So nodes you allocated for `5` and `3` became unreachable (memory leak).

---

## 🧩 Step-by-step diagram (Insert at Head)

Start:

```
head = NULL
```

### Insert 7

```
new_node = [7 | NULL]
return new_node

head
 |
 v
[7 | NULL]
```

### Insert 5

```
new_node = [5 | ?]
new_node->next = head

head
 |
 v
[7 | NULL]

becomes

head
 |
 v
[5 |  *-] ---> [7 | NULL]
```

### Insert 3

```
head
 |
 v
[3 |  *-] ---> [5 |  *-] ---> [7 | NULL]
```

So `print_list(head)` prints:

```
3, 5, 7
```

---

## 🧵 Insert at Tail (lesson #2)

### ✅ What "insert at tail" means

You want the new node to become the **last** element.

That means:

* if list is empty → new node becomes head
* otherwise traverse to the last node and attach

### Insert at tail function (same naming style)

```c
Node *insert_at_tail(Node *head, int new_value)
{
	Node *new_node;
	Node *current;

	new_node = calloc(1, sizeof(Node));
	if (!new_node)
		return (head);

	new_node->value = new_value;
	new_node->next = NULL;

	if (head == NULL)
		return (new_node);

	current = head;
	while (current->next != NULL)
		current = current->next;

	current->next = new_node;
	return (head);
}
```

---

## 🧩 Step-by-step diagram (Insert at Tail)

Start:

```
head = NULL
```

### Insert 7 at tail

```
head
 |
 v
[7 | NULL]
```

### Insert 5 at tail

We walk until `current->next == NULL` (we find 7).
Then:

```
[7 | NULL]  becomes  [7 | *-] ---> [5 | NULL]
```

### Insert 3 at tail

We walk: 7 -> 5 (stop at 5).
Then:

```
head
 |
 v
[7 | *-] ---> [5 | *-] ---> [3 | NULL]
```

So printing gives:

```
7, 5, 3
```

✅ Notice the difference:

* insert at head reverses order (last inserted shows first)
* insert at tail keeps insertion order

---

## 🖨️ Printing the list (your function)

Your `print_list` is correct:

```c
void print_list(Node *head)
{
	Node *current;
	int i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		printf("Node %d: %d\n", i, current->value);
		i++;
		current = current->next;
	}
}
```

---

## 🧠 Deep understanding (the rule you must remember)

### ✅ Head insertion rule

```
new_node->next = head;
head = new_node;
```

### ✅ Tail insertion rule

```
find last node
last->next = new_node;
```

---

## 🧹 Important: freeing memory (good habit)

Every `calloc` must eventually be freed.

```c
void free_list(Node *head)
{
	Node *tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
```

Call it at the end of `main`:

```c
free_list(list1_head);
```

---

## 🧪 Quick test expectations

### If you use insert at head:

```c
list1_head = insert_at_head(list1_head, 7);
list1_head = insert_at_head(list1_head, 5);
list1_head = insert_at_head(list1_head, 3);
```

Output should be:

```
Node 0: 3
Node 1: 5
Node 2: 7
```

### If you use insert at tail:

Output should be:

```
Node 0: 7
Node 1: 5
Node 2: 3
```

---

## ✅ Peer Evaluation Q&A (common questions)

### Q1) Why do we return `Node *` from insert functions?

Because the head might change.

* insert at head always changes head
* insert at tail changes head only when the list is empty

### Q2) Why is `new_node->next = head` so important?

Because that’s the **link**.
Without it you don’t connect nodes, you just allocate memory and lose it.

### Q3) Why do we traverse using `current`?

Because you must not lose the head pointer.
`current` is a “walker” pointer used to move through the list safely.

---

## ✅ Final mental picture

A linked list is nothing more than:

* nodes in heap
* one pointer (head) in stack
* each node stores the address of the next node

If you break one link (`next`), everything after it becomes unreachable.

---

```


