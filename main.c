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

int main(int argc, char *argv[])
{
	t_node *table;
	t_data *args;

	int	*is_running;
	is_running = (int *)malloc(sizeof(int));
	is_running[0] = 1;

	args->is_running = is_running;
	args = check_valid_arguments_and_struct(argc, argv);
	table = create_table_and_fill_with_n_philosophers(args->number_of_philosophers, args);
	run_the_last_supper_simulation(table, args);
	free_args_and_table(table, args);
	free(is_running);
	return (0);
}
