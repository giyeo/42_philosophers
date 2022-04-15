#include "philo.h"

t_data  *check_valid_arguments_and_struct(int argc, char *argv[])
{
	t_data *args;

	argc--;
	correct_arguments(argc, argv);
	args = (t_data *)malloc(1);
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 5)
		args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	return args;
}

/* create_philosophers
Each philosopher has a number ranging from 1 to number_of_philosophers.

Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
*/

//circle *create_philosophers(int number_of_philosophers);

/*
Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.

• A displayed state message should not be mixed up with another message.

• A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.

• Again, philosophers should avoid dying!
*/

void	print_philo_stats(int time, int index, char *stat)
{
	if(!strcmp(stat, "eating")
	|| !strcmp(stat, "sleeping")
	|| !strcmp(stat, "thinking"))
		printf("%d %d is %s\n", time, index, stat);
	else if (!strcmp(stat, "fork"))
		printf("%d %d has taken a fork\n", time, index);
	else
		printf("%d %d died\n", time, index);
}

t_node *create_table_and_fill_with_n_philosophers(int number_of_philosophers)
{
	t_node *table;
	int i;

	i = 1;
	table = insert_node(NULL, 1);
	while(i < number_of_philosophers)
		insert_node(table, i++ + 1);
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

void *nothing(void *vargp){
	static int i = 0;
	i++;
	printf("[%d]\n", i);
	return NULL;
}

void print_table(t_node *table)
{
	while(!table->last)
	{
		printf("{ philo %d }\n", table->index);
		table = table->next;
	}
	printf("{ philo %d }\n", table->index);
}

void	free_args_and_table(t_node *table, t_data *args)
{
	free(args);
	free_table(table);
}

void	create_threads_pair_and_odd(int is_odd, t_node *table)
{
	while(!table->last)
	{
		if((table->index % 2) == is_odd)
		{
			pthread_create(&table->thread_id, NULL, nothing, NULL);
			printf("%ld\n", table->thread_id);
		}
		table = table->next;
	}
	if((table->index % 2) == is_odd)
	{
		pthread_create(&table->thread_id, NULL, nothing, NULL);
		printf("%ld\n", table->thread_id);
	}
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

void	run_the_last_supper_simulation(t_node *table, t_data *args)
{
	print_table(table);
	print_args(args);

	init_mutex(table);
	create_threads_pair_and_odd(1, table);
	usleep(5);
	create_threads_pair_and_odd(0, table);

	exit(1);
}

void *philosopher_lifecycle(void *vargp)
{
	t_node *myself = (t_node *)vargp;
	t_node *left_neighboor = myself->previous;

	while(1)
	{
		pthread_mutex_lock(&left_neighboor->fork);
		printf("%d has taken a fork", myself->index);
		pthread_mutex_lock(&myself->fork);
		printf("%d has taken a fork", myself->index);
		printf("%d is eating", myself->index);
		usleep(myself->time_to_eat);
		pthread_mutex_unlock(&left_neighboor->fork);
		pthread_mutex_unlock(&myself->fork);
		printf("%d is sleeping", myself->index);
		usleep(myself->time_to_sleep);
		printf("%d is thinking", myself->index);
	}
}

int main(int argc, char *argv[])
{
	t_node *table;
	t_data *args;

	args = check_valid_arguments_and_struct(argc, argv);
	table = create_table_and_fill_with_n_philosophers(args->number_of_philosophers);
	run_the_last_supper_simulation(table, args);

	free_args_and_table(table, args);
	return (0);
}
