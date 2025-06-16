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
	}
	return ((single_count % 2) + (double_count % 2));
}

int	is_meta(char *str)
{
	if (str[0] == ' ' || str[0] == '\t' || str[0] == '\v' || str[0] == '\n'
		|| str[0] == '<' || str[0] == '(' || str[0] == ')' || str[0] == '>'
		|| str[0] == '|' || (str[0] == '&' && str[1] == '&'))
		return (1);
}

t_token	*tokenisation(char *str)
{
	if (check_quotes(str))
		return (puterr(Q_ERR), NULL);

}
