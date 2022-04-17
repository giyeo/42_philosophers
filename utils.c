/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:15:11 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 18:35:07 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ischardigit(char var)
{
	if ((var >= 48 && var <= 57) || var == 45 || var == 43)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *pointer)
{
	size_t	counter;

	counter = 0;
	while (pointer[counter] != '\0')
		counter++;
	return (counter);
}

long int	time_since_big_bang(long int start_time)
{
	struct timeval	current_time;
	long int		current_t;

	gettimeofday(&current_time, NULL);
	current_t = current_time.tv_sec * 1000000 + current_time.tv_usec;
	return ((current_t - start_time) / 1000);
}

long int	actual_time(void)
{
	struct timeval	current_time;
	long int		current_t;

	gettimeofday(&current_time, NULL);
	current_t = current_time.tv_sec * 1000000 + current_time.tv_usec;
	return (current_t);
}

int	print(t_node *myself, char *text)
{
	if (!myself->is_running[0])
		return (1);
	printf("%ld %d %s\n", time_since_big_bang(myself->start_time),
		myself->index, text);
	return (0);
}
