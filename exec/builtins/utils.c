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
