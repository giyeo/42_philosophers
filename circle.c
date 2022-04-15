#include "philo.h"

t_node	*create_circular(int index)
{
	t_node *node;
	node = (t_node *)malloc(sizeof(t_node) * 1);
	node->next = node;
	node->previous = node;
	node->last = 1;

	node->index = index;
	return node;
}

t_node	*insert_node(t_node *list, int index)
{
	t_node *new;

	if(list == NULL)
		return create_circular(index);
	new = (t_node *)malloc(sizeof(t_node) * 1);

	new->index = index;
	new->last = 1;
	while(!list->last)
		list = list->next;
	list->last = 0;
	new->next = list->next;
	new->previous = list;
	list->next = new;
	new->next->previous = new;

	return NULL;
}
