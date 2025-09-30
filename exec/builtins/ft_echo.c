#include "minishell.h"

static int	is_raw_n(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (args && args[0] && is_raw_n(args[0]))
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
