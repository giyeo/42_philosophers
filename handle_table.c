#include "philo.h"

t_node *create_table_and_fill_with_n_philosophers(int number_of_philosophers, t_data *args)
{
	t_node *table;
	struct timeval current_time;
	long int start_time;
	int i;

	gettimeofday(&current_time, NULL);
	start_time = current_time.tv_sec * 1000000 + current_time.tv_usec;

	args->start_time = start_time;
	i = 1;
	table = insert_node(NULL, 1, args);
	while(i < number_of_philosophers)
		insert_node(table, i++ + 1, args);
	return table;
}

void	free_table(t_node *table)
{
	while(!table->last)
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
	while(!table->last)
	{
		pthread_mutex_init(&table->fork, NULL);
		table = table->next;
	}
	pthread_mutex_init(&table->fork, NULL);
}
