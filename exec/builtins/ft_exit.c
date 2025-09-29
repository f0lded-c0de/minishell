#include "minishell.h"

static int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(int ac, char **args)
{
	unsigned long long	exit_code;

	exit_code = 0;
	if (ac > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		free_split(args);
		return (1);
	}
	if (ac == 2)
	{
		if (!ft_strisdigit(args[1]))
		{
			write(2, "exit: numeric argument required\n", 32);
			free_split(args);
			exit(2);
		}
		exit_code = ft_atoull(args[1]);
		if (exit_code >= LLONG_MAX)
		{
			write(2, "exit: numeric argument required\n", 32);
			free_split(args);
			exit(2);
		}
		free_split(args);
		exit((int)exit_code);
	}
	free_split(args);
	exit(0);
}
