#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t list_len(const list_t *h)
{/* 1. initialize count as 0 */
	size_t i = 0;
	/* 2. loop through list and increment count */
	while (h)
	{
		h = h->next; /* 3. move to next node */
		i++; /* 4. increment count */
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head; /* 1. initialize node to head */
	size_t i = list_len(head), j; /* 2. get size of list */
	char **strs; /* 3. initialize array of strings */
	char *str; /* 4. initialize string */
	/* 5. allocate memory for array of strings */
	if (!head || !i) /* 6. if list is empty, return NULL */
		return (NULL); /* 7. loop through list and copy strings */
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs) /* 8. if malloc fails, return NULL */
		return (NULL); /* 9. copy strings */
	for (i = 0; node; node = node->next, i++) /* 10. increment count */
	{/* 11. allocate memory for string */
		str = malloc(_strlen(node->str) + 1);
		if (!str) /* 12. if malloc fails, free strs and return NULL */
		{/* 13. free strs */
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs); /* 14. return NULL */
			return (NULL); /* 15. copy string */
		}

		str = _strcpy(str, node->str); /* 16. set strs[i] to string */
		strs[i] = str;
	}
	strs[i] = NULL; /* 17. set strs[i] to NULL */
	return (strs); /* 18. return array of strings */
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node); /* match */
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
