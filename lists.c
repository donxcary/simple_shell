#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head; /* new head node */

	if (!head)
		return (NULL); /* return if head is NULL */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL); /* return if malloc fails */
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num; /* set num field of new head node */
	if (str)
	{
		new_head->str = _strdup(str); /* set str field of new head node */
		if (!new_head->str)
		{
			free(new_head); /* free new_head if strdup fails */
			return (NULL);
		}
	}
	new_head->next = *head; /* set next field of new head node */
	*head = new_head;  /* set head to new head node */
	return (new_head); /* return new head node */
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node; /* new node and current node */

	if (!head)
		return (NULL); /* return if head is NULL */

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL); /* return if malloc fails */
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num; /* set num field of new node */
	if (str)
	{
		new_node->str = _strdup(str); /* set str field of new node */
		if (!new_node->str) /* return if strdup fails */
		{
			free(new_node); /* free new_node if strdup fails */
			return (NULL); /* return if strdup fails */
		}
	}
	if (node)
	{
		while (node->next) /* traverse to last node */
			node = node->next;
		node->next = new_node; /* set next field of last node */
	}
	else
		*head = new_node; /* set head to new node if list is empty */
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0; /* number of nodes */

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next; /* traverse to next node */
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0); /* return if list is empty */

	if (!index)
	{
		node = *head;
		*head = (*head)->next; /* set head to next node */
		free(node->str); /* free str field of node */
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next; /* set prev node's next to next */
			free(node->str); /* free str field of node */
			free(node);
			return (1);
		}
		i++;
		prev_node = node; /* set prev node to current node */
		node = node->next; /* traverse to next node */
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head; /* set node to head */
	while (node)
	{
		next_node = node->next; /* set next node */
		free(node->str); /* free str field of node */
		free(node);
		node = next_node;
	}
	*head_ptr = NULL; /* set head to NULL */
}
