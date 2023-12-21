#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL); /* no head pointer */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL); /* malloc fail */
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num; /* set node index */
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head); /* malloc fail */
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head; /* set head pointer */
	return (new_head); /* return new head */
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
	list_t *new_node, *node;
	/* list_t *new_node = malloc(sizeof(list_t)); */
	if (!head)
		return (NULL);

/* if (!new_node) */
/* return (NULL); */
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL); /* malloc fail */
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num; /* set node index */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;
	/* list_t *node = h; */
	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++; /* count nodes */
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0; /* node index */
	/* list_t *node = *head; */
	if (!head || !*head)
		return (0);
	/* if index is 0, delete first node */
	if (!index)
	{
		node = *head; /* set node to first node */
		*head = (*head)->next; /* set head to next node */
		free(node->str); /* free str */
		free(node); /* free first node */
		return (1); /* success */
	}
	node = *head; /* set node to first node */
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node); /* free node */
			return (1);
		}
		i++; /* increment node index */
		prev_node = node;
		node = node->next; /* set node to next node */
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
	/* list_t *node = *head_ptr; */
	if (!head_ptr || !*head_ptr)
		return; /* no list */
	head = *head_ptr;
	node = head;
	while (node)
	{/* free each node */
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
