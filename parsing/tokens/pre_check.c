#include "minishell.h"

int	check_quotes(char *str)
{
	int	single_count;
	int	double_count;
	int	i;

	single_count = 0;
	double_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(double_count % 2))
			single_count++;
		if (str[i] == '"' && !(single_count % 2))
			double_count++;
		i++;
	}
	if ((single_count % 2) || (double_count % 2))
		return (puterr(QUO_ERR), 0);
	return (1);
}

int	check_parenthesis(char *str)
{
	int	open_count;
	int	close_count;
	int	i;

	open_count = 0;
	close_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			open_count++;
		if (str[i] == ')')
			close_count++;
		i++;
	}
	if (open_count != close_count)
		return (puterr(PAR_ERR), 0);
	return (1);
}
