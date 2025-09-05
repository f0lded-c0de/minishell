#include "minishell.h"

int	valid_varname(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A'
				&& name[0] <= 'Z') || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A'
					&& name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

unsigned long long	ft_atoull(const char *str)
{
	int		i;
	unsigned long long	n;
	unsigned long long	dest;

	i = 0;
	n = 1;
	dest = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
				n = n * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		dest = ((dest * 10) + (str[i] - '0'));
		i++;
	}
	return (((dest * n) % 256 + 256) % 256);
}

