#include "exec.h"
#include <climits>
#include <cstdlib>

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
		return (1);
	}
	if (ac == 2) 
	{
		if (!ft_strisdigit(args[1]))
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(2);
		}
		exit_code = ft_atoi_custom(args[1]);
		if (exit_code >= LLONG_MAX)
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(2);
		}
		exit((int)exit_code);
	}
	exit(0);
}
