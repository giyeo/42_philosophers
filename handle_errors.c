#include "philo.h"

void	isnumber_handler(int argc, char *argv[])
{
	int		i;
	int		j;
	int		length;
	char	*string;

	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		string = argv[i++ + 1];
		length = ft_strlen(string);
		if (length == 0)
			exit(1);
		while (j < length)
		{
			if (!ischardigit(string[j++]))
            {
				printf("%c\n", string[j]);
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
