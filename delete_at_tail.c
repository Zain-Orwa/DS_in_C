#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
} Node;

void print_list(Node *head);
Node *insert_at_head(Node *head, int new_value);
Node *insert_at_tail(Node *head, int new_value);
Node *delete_at_head(Node *head);
Node *delete_at_tail(Node *head);



int main(void)
{
	Node *list1_head = NULL;

	list1_head = insert_at_head(list1_head, 7);
	list1_head = insert_at_head(list1_head, 5);
	list1_head = insert_at_head(list1_head, 3);

	printf("Before Delete:\n");
	print_list(list1_head);

	printf("\nAfter Deleting head:\n");
	list1_head = delete_at_head(list1_head);
	print_list(list1_head);

	printf("\nAfter Deleting tail:\n");
	list1_head = delete_at_tail(list1_head);
	print_list(list1_head);

	return (0);
}

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

Node *delete_at_head(Node *head){
  if (head == NULL) return (NULL);
  else
  {
    Node *to_return = head->next;
    free(head);
    return (to_return);
  }
}

Node *insert_at_tail(Node *head, int new_value){
	Node *new_node = calloc(1, sizeof(Node));
	new_node->value = new_value;
	if (head == NULL) return (new_node);
	else
	{
		Node *current = head;
		while (current->next != NULL) current = current->next;
		current->next = new_node;
		return (head);
	}
}

Node *insert_at_head(Node *head, int new_value){
	Node *new_node = calloc(1, sizeof(Node));
	new_node->value = new_value;
	if (head == NULL) return (new_node);
	else
	{
		new_node->next = head;
		return (new_node);
	}

}

void print_list(Node *head){
	Node *current;
	current = head;
	int i;

	i = 0;
	while (current != NULL)
	{
		printf("Node %d: %d\n", i, current->value);	
		i++;
		current = current->next;
	}
}





