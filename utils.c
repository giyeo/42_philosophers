#include "philo.h"

void    print_args(t_data *args)
{
    printf("philos: %d, time_to_die: %d, time_to_eat: %d, time_to_sleep: %d, number_of_times: %d\n",
    args->number_of_philosophers,
    args->time_to_die, args->time_to_eat,
    args->time_to_sleep,
    args->number_of_times_each_philosopher_must_eat);
}

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
