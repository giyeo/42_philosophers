#include "philo.h"

void	isnumber_handler(int argc, char *argv[])
{
	int		i;
	int		j;
	int		lenght;
	char	*string;

	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		string = argv[i++ + 1];
		lenght = ft_strlen(string);
		if (lenght == 0)
			exit(1);
		while (j < lenght)
		{
			if (!ischardigit(string[j++]))
            {
				printf("only numbers! \n");
                exit(1);
            }
		}
	}
}

void    correct_arguments(int argc, char *argv[])
{
    isnumber_handler(argc + 1, argv);
    if(argc < 4 || argc > 5)
    {
        if(argc < 4)
            printf("Not enough arguments! \n");
        else
            printf("So many arguments! \n");
        exit(1);
    }
}
