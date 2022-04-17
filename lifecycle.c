#include "philo.h"

long int	time_since_big_bang(long int start_time)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long int current_t = current_time.tv_sec * 1000000 + current_time.tv_usec;

	return ((current_t - start_time) / 1000);
}

long int	actual_time(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long int current_t = current_time.tv_sec * 1000000 + current_time.tv_usec;

	return current_t;
}

int	print(t_node *myself, char *text)
{
	if(!myself->is_running[0])
		return 1;
	printf("%ld %d %s\n", time_since_big_bang(myself->start_time), myself->index, text);
	return 0;
}

void	eat(int *times_eaten, t_node *myself, t_node *left_neighboor)
{
	usleep(myself->time_to_eat * 1000);
	myself->last_eat_time = actual_time();
	(*times_eaten)++;
	if(*times_eaten == myself->number_of_times_each_philosopher_must_eat)
		myself->feed = 1;
	pthread_mutex_unlock(&left_neighboor->fork);
	pthread_mutex_unlock(&myself->fork);
}

void	*philosopher_lifecycle(void *vargp)
{
	t_node *myself = (t_node *)vargp;
	t_node *left_neighboor = myself->previous;
	int times_eaten = 0;

	while(1)
	{
		pthread_mutex_lock(&myself->fork);
		if(print(myself, "has taken a fork"))
			break;
		if(myself->number_of_philosophers > 1)
			pthread_mutex_lock(&left_neighboor->fork);
		else
			break;
		if(print(myself, "has taken a fork"))
			break;
		if(print(myself, "is eating"))
			break;
		eat(&times_eaten, myself, left_neighboor);
		if(print(myself, "is sleeping"))
			break;
		usleep(myself->time_to_sleep * 1000);
		if(print(myself, "is thinking"))
			break;
	}
	//printf("%d terminated\n", myself->index);
}

void	create_threads_pair_and_odd(int is_odd, t_node *table)
{
	while(!table->last)
	{
		if((table->index % 2) == is_odd)
			pthread_create(&table->thread_id, NULL, philosopher_lifecycle, table);
		table = table->next;
	}
	if((table->index % 2) == is_odd)
		pthread_create(&table->thread_id, NULL, philosopher_lifecycle, table);
}

void *monitor(void *vargp)
{
	t_node *table = (t_node *)vargp;
	int counter = 0;
	while(1)
	{
		if((actual_time() - table->last_eat_time) > table->time_to_die * 1000)
		{
			table->is_running[0] = 0;
			printf("%ld %d died\n", ((actual_time() - table->start_time) / 1000), table->index);
			printf("time_not_eating %ld > %d time_to_die\n", actual_time() - table->last_eat_time, table->time_to_die * 1000);
			break ;
		}
		table = table->next;
		if(table->feed)
			counter++;
		if(counter == table->number_of_philosophers)
		{
			table->is_running[0] = 0;
			break ;
		}
		if(table->last)
			counter = 0;
	}
	//printf("monitor terminated\n");
	//check if all philosophers are dead or feed and if so, free the table and args then exit;
}

void	run_the_last_supper_simulation(t_node *table, t_data *args)
{
	pthread_t	monitor_id;
	// print_table(table);
	// print_args(args);
	int i = 0;
	init_mutex(table);
	create_threads_pair_and_odd(1, table);
	usleep(5);
	create_threads_pair_and_odd(0, table);

	pthread_create(&monitor_id, NULL, monitor, table);
	while(i < args->number_of_philosophers)
	{
		pthread_join(table->thread_id, NULL);
		i++;
		table = table->next;
	}
	pthread_join(monitor_id, NULL);
}
