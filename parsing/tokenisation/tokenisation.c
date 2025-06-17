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

t_tkn	*tokenisation(char *str)
{
	t_tkn	tokens;
	int	i;
	int	move;

	if (check_quotes(str), check_parenthesis(str))
		return (NULL);
	if (!str[0])
		return (tkn_new("", EMPTY));
	i = 0;
	move = 0;
	tokens = NULL;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i])
			tokens = get_token(tokens, &str[i], &move);
		if (!tokens)
			return (NULL);
		i += move;
	}
}
