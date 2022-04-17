/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:31:38 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 20:42:15 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_node *myself, t_node *left_neighboor)
{
	myself->last_eat_time = actual_time();
	usleep(myself->time_to_eat * 1000);
	myself->times_eaten++;
	if (myself->times_eaten == myself->times_must_eat)
		myself->feed = 1;
	pthread_mutex_unlock(&left_neighboor->fork);
	pthread_mutex_unlock(&myself->fork);
}

void	*philosopher_lifecycle(void *vargp)
{
	t_node	*myself;

	myself = (t_node *)vargp;
	myself->times_eaten = 0;
	while (1)
	{
		pthread_mutex_lock(&myself->fork);
		if (print(myself, "has taken a fork"))
			break ;
		if (myself->number_of_philosophers > 1)
			pthread_mutex_lock(&myself->previous->fork);
		else
			break ;
		if (print(myself, "has taken a fork"))
			break ;
		if (print(myself, "is eating"))
			break ;
		eat(myself, myself->previous);
		if (print(myself, "is sleeping"))
			break ;
		usleep(myself->time_to_sleep * 1000);
		if (print(myself, "is thinking"))
			break ;
	}
	return (NULL);
}

void	create_threads_pair_and_odd(int is_odd, t_node *table)
{
	while (!table->last)
	{
		if ((table->index % 2) == is_odd)
			pthread_create(&table->thread_id, NULL,
				philosopher_lifecycle, table);
		table = table->next;
	}
	if ((table->index % 2) == is_odd)
		pthread_create(&table->thread_id, NULL, philosopher_lifecycle, table);
}

void	*monitor(void *vargp)
{
	t_node	*table;
	int		counter;

	counter = 0;
	table = (t_node *)vargp;
	while (1)
	{
		if ((actual_time() - table->last_eat_time) > table->time_to_die * 1000)
		{
			table->is_running[0] = 0;
			printf("%6ld %d died\n",
				((actual_time() - table->start_time) / 1000), table->index);
			break ;
		}
		table = table->next;
		if (table->feed)
			counter++;
		if (everyone_is_fed(counter, table))
			break ;
		if (table->last)
			counter = 0;
	}
	return (NULL);
}

void	run_the_last_supper_simulation(t_node *table, t_data *args)
{
	pthread_t	monitor_id;
	int			i;

	i = 0;
	init_mutex(table);
	create_threads_pair_and_odd(1, table);
	usleep(5);
	create_threads_pair_and_odd(0, table);
	pthread_create(&monitor_id, NULL, monitor, table);
	while (i < args->number_of_philosophers)
	{
		pthread_join(table->thread_id, NULL);
		i++;
		table = table->next;
	}
	pthread_join(monitor_id, NULL);
}
