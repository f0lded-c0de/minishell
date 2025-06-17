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
		return (puterr(Q_ERR), 0);
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
		return (puterr(P_ERR), 0);
	return (1);
}

int	is_meta(char *str)
{
	if (str[0] == ' ' || str[0] == '\t' || str[0] == '\v' || str[0] == '\n'
		|| str[0] == '<' || str[0] == '(' || str[0] == ')' || str[0] == '>'
		|| str[0] == '|' || (str[0] == '&' && str[1] == '&'))
		return (1);
}

t_tkn	*tokenisation(char *str)
{
	if (check_quotes(str), check_parenthesis(str))
		return (NULL);
	if (!str[0])
		return (tkn_new(NULL, EMPTY));
}
