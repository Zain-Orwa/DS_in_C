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

# ➖ Deleting Nodes (Head & Tail)

Now the list already works.
Insertion builds the chain.

Deletion is the opposite operation:
we must **remove a node AND repair the chain**.

Very important rule:

> In linked lists you never “erase a value”  
> you erase the node AND reconnect the neighbors

---

## 🧠 The danger when deleting
If you `free()` a node but another pointer still points to it:

→ you create a **dangling pointer**
→ accessing it = undefined behavior / crash

So every delete operation always has TWO jobs:

1) Save where the list must continue
2) Free the removed node

---

# 🗑️ Delete at Head

```c
Node *delete_at_head(Node *head){
  if (head == NULL) return (NULL);
  else
  {
    Node *to_return = head->next;
    free(head);
    return (to_return);
  }
}
````

---

## Step-by-step memory view

Current list:

```
head
 |
 v
[3 | *-] ---> [5 | *-] ---> [7 | NULL]
```

### Step 1 — Save next node

```
to_return = head->next

to_return
 |
 v
[5 | *-] ---> [7 | NULL]
```

### Step 2 — Free old head

```
free(head)
```

The node `[3]` disappears from heap.

### Step 3 — Return new head

```
head becomes to_return

head
 |
 v
[5 | *-] ---> [7 | NULL]
```

---

## Memory layout (stack vs heap)

Before delete:

```
STACK                       HEAP
list1_head  ---------->   [3 | *] -> [5 | *] -> [7 | NULL]
```

After delete:

```
STACK                       HEAP
list1_head  ---------->   [5 | *] -> [7 | NULL]

( node 3 freed )
```

---

## Key idea

Head deletion is simple because:

> The list already stores the next node for us

We just move the head forward.

Time complexity: **O(1)**

---

# 🗑️ Delete at Tail

This one is harder.

Why?

Because nodes do NOT know who points to them.

The last node cannot be removed directly —
we must first find the node BEFORE it.

---

```c
Node *delete_at_tail(Node *head)
{
  if (head == NULL) return (NULL);

  else if (head->next == NULL)
  {
    free(head);
    return (NULL);
  }

  else
  {
    Node *current = head;
    Node *prev = NULL;

    while (current->next != NULL)
    {
      prev = current;
      current = current->next;
    }

    prev->next = NULL;
    free(current);
    return (head);
  }
}
```

---

## Step-by-step diagram

Starting list:

```
head
 |
 v
[3 | *] ---> [5 | *] ---> [7 | NULL]
```

### Traversal phase

We move two pointers:

```
prev      current
 |           |
 v           v
[3] ----> [5] ----> [7]
```

Loop ends when `current->next == NULL`

So:

```
prev = [5]
current = [7]
```

---

### Disconnect last node

```
prev->next = NULL
```

Now:

```
[3] ---> [5] ---> NULL     [7] (isolated)
```

### Free last node

```
free(current)
```

Final list:

```
head
 |
 v
[3 | *] ---> [5 | NULL]
```

---

## Memory layout

Before:

```
STACK                        HEAP
list1_head  ---------->   [3] -> [5] -> [7]
```

After:

```
STACK                        HEAP
list1_head  ---------->   [3] -> [5]

(node 7 freed)
```

---

## Special case — single element list

```
head -> [7 | NULL]
```

We delete tail:

```
free(head)
return NULL
```

Now list becomes empty again.

---

## Why we used two pointers (prev & current)

Because singly linked list only knows → next

It does NOT know → previous

So we simulate "previous" manually while walking.

This is the most important linked list traversal pattern:

```
prev = current
current = current->next
```

You will use this pattern in:

* delete specific value
* reverse list
* insert in middle
* sorting list

---

## Complexity comparison

| Operation      | Time |
| -------------- | ---- |
| delete_at_head | O(1) |
| delete_at_tail | O(n) |

Reason:
Head already known
Tail must be searched

---

## Mental model to remember

Linked list operations always follow this law:

> When adding → connect new node
> When deleting → reconnect neighbors

---

## Final execution of your program

Initial insertions (head insert):

```
3 -> 5 -> 7
```

After deleting head:

```
5 -> 7
```

After deleting tail:

```
5
```

Program output:

```
Before Delete:
Node 0: 3
Node 1: 5
Node 2: 7

After Deleting head:
Node 0: 5
Node 1: 7

After Deleting tail:
Node 0: 5
```

---

## Common beginner mistakes avoided here

1. Freeing before saving next pointer
2. Losing head pointer
3. Forgetting single-node case
4. Not setting prev->next = NULL
5. Accessing freed memory

---

