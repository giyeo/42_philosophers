/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:22:05 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 22:23:10 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*check_valid_arguments_and_struct(int argc, char *argv[])
{
	t_data	*args;

	argc--;
	correct_arguments(argc, argv);
	args = (t_data *)malloc(sizeof(t_data) * 1);
	args->number_of_philosophers = atoi(argv[1]);
	if (args->number_of_philosophers <= 0)
	{
		free(args);
		printf("must have at least 1 philosopher\n");
		exit(1);
	}
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 5)
		args->times_must_eat = atoi(argv[5]);
	return (args);
}

int	main(int argc, char *argv[])
{
	t_node	*table;
	t_data	*args;
	int		*is_running;

	is_running = (int *)malloc(sizeof(int));
	is_running[0] = 1;
	args = check_valid_arguments_and_struct(argc, argv);
	args->is_running = is_running;
	table = create_table_and_fill_with_n_philosophers
		(args->number_of_philosophers, args);
	run_the_last_supper_simulation(table, args);
	free_args_and_table(table, args);
	free(is_running);
	return (0);
}
