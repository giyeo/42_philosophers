/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:24:00 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 20:43:23 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*create_circular(int index, t_data *args)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node) * 1);
	node->next = node;
	node->previous = node;
	node->last = 1;
	node->index = index;
	node->time_to_die = args->time_to_die;
	node->time_to_eat = args->time_to_eat;
	node->time_to_sleep = args->time_to_sleep;
	node->times_must_eat = args->times_must_eat;
	node->start_time = args->start_time;
	node->last_eat_time = args->start_time;
	node->is_running = args->is_running;
	node->feed = 0;
	node->number_of_philosophers = args->number_of_philosophers;
	return (node);
}

t_node	*insert_node(t_node *list, int index, t_data *args)
{
	t_node	*new;

	if (list == NULL)
		return (create_circular(index, args));
	new = (t_node *)malloc(sizeof(t_node) * 1);
	new->index = index;
	new->last = 1;
	while (!list->last)
		list = list->next;
	list->last = 0;
	new->next = list->next;
	new->previous = list;
	list->next = new;
	new->next->previous = new;
	new->time_to_die = args->time_to_die;
	new->time_to_eat = args->time_to_eat;
	new->time_to_sleep = args->time_to_sleep;
	new->times_must_eat = args->times_must_eat;
	new->start_time = args->start_time;
	new->last_eat_time = args->start_time;
	new->is_running = args->is_running;
	new->feed = 0;
	new->number_of_philosophers = args->number_of_philosophers;
	return (NULL);
}
