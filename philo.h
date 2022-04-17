/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:19:10 by rpaulino          #+#    #+#             */
/*   Updated: 2022/04/17 18:36:58 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct t_node
{
	int				index;
	int				last;
	long int		last_eat_time;
	pthread_mutex_t	fork;
	pthread_t		thread_id;
	struct t_node	*next;
	struct t_node	*previous;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long int		start_time;
	int				*is_running;
	int				feed;
	int				number_of_philosophers;
}					t_node;

typedef struct s_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	long int	start_time;
	int			*is_running;
}					t_data;

// LINKED LIST CONTROL
t_node		*insert_node(t_node *list, int index, t_data *args);
t_node		*create_circular(int index, t_data *args);

// UTILS
void		print_args(t_data *args);
int			ischardigit(char var);
size_t		ft_strlen(const char *pointer);
void		print_table(t_node *table);
void		print_philo_stats(int time, int index, char *stat);

// HANDLE ERRORS
void		correct_arguments(int argc, char *argv[]);
void		isnumber_handler(int argc, char *argv[]);

// HANDLE TABLE
t_node		*create_table_and_fill_with_n_philosophers(
				int number_of_philosophers, t_data *args);
void		free_table(t_node *table);
void		free_args_and_table(t_node *table, t_data *args);
void		init_mutex(t_node *table);

// SIMULATION
void		*philosopher_lifecycle(void *vargp);
void		run_the_last_supper_simulation(t_node *table, t_data *args);
long int	time_since_big_bang(long int start_time);
long int	actual_time(void);
int			print(t_node *myself, char *text);
#endif