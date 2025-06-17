#include "exec.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (args && args[0] && ft_strncmp(args[0], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
