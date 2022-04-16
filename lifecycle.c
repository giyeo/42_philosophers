#include "philo.h"

void *philosopher_lifecycle(void *vargp)
{
	t_data_and_node *object = (t_data_and_node *) vargp;
	t_data *args = object->args;
	t_node *myself = object->table;
	t_node *left_neighboor = myself->previous;

    return ;
	while(1)
	{
		pthread_mutex_lock(&left_neighboor->fork);
		printf("%d has taken a fork", myself->index);
		pthread_mutex_lock(&myself->fork);
		printf("%d has taken a fork", myself->index);
		printf("%d is eating", myself->index);
		usleep(args->time_to_eat);
		pthread_mutex_unlock(&left_neighboor->fork);
		pthread_mutex_unlock(&myself->fork);
		printf("%d is sleeping", myself->index);
		usleep(args->time_to_sleep);
		printf("%d is thinking", myself->index);
	}
}
