
#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct t_node
{
	int				index;
	int				last;
	int				last_eat_time;
	pthread_mutex_t	fork;
	pthread_t		thread_id;
	struct t_node	*next;
	struct t_node	*previous;
}					t_node;

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    struct timeval start_time;
}					t_data;

typedef struct s_data_and_node
{
	t_data *args;
	t_node *table;
}					t_data_and_node;

// LINKED LIST CONTROL
t_node	*insert_node(t_node *list, int index);
t_node	*create_circular(int index);

// UTILS
void   	print_args(t_data *args);
int		ischardigit(char var);
size_t	ft_strlen(const char *pointer);

// HANDLE ERRORS
void    correct_arguments(int argc, char *argv[]);
void	isnumber_handler(int argc, char *argv[]);

// SIMULATION
void	*philosopher_lifecycle(void *vargp);
#endif