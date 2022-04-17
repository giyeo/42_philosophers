/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:29:55 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 18:29:55 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*create_table_and_fill_with_n_philosophers(int number_of_philosophers,
	t_data *args)
{
	struct timeval	current_time;
	long int		start_time;
	t_node			*table;
	int				i;

	i = 1;
	gettimeofday(&current_time, NULL);
	start_time = current_time.tv_sec * 1000000 + current_time.tv_usec;
	args->start_time = start_time;
	table = insert_node(NULL, 1, args);
	while (i < number_of_philosophers)
		insert_node(table, i++ + 1, args);
	return (table);
}

void	free_table(t_node *table)
{
	while (!table->last)
	{
		table = table->next;
		free(table->previous);
	}
	free(table);
}

void	free_args_and_table(t_node *table, t_data *args)
{
	free(args);
	free_table(table);
}

void	init_mutex(t_node *table)
{
	while (!table->last)
	{
		pthread_mutex_init(&table->fork, NULL);
		table = table->next;
	}
	pthread_mutex_init(&table->fork, NULL);
}

int	everyone_is_fed(int counter, t_node *table)
{
	if (counter == table->number_of_philosophers)
	{
		table->is_running[0] = 0;
		return (1);
	}
	return (0);
}
