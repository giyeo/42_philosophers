/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:15:11 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 18:17:45 by rpaulino         ###   ########.fr       */
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
