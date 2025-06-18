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

t_tkn	*token_delimiter(t_tkn **head, char **tmp, char c)
{
	t_tkn	*new;

	new = tkn_new(*tmp);
	if (!new)
		return (tkn_free(*head), free(*tmp), NULL);
	tkn_append(head, new);
	*tmp = NULL;
	if (!is_space(c))
		*tmp = str_append_char(c);
	return (*head);
}

t_quote	handle_quotes(char *tmp, char c, t_quote value)
{

}

t_tkn	*tokenisation(char *str)
{
	t_tkn	head;
	char	*tmp;
	t_quote	in_quote;
	int		i;

	if (!str[0])
		return (NULL);
	if (check_quotes(str), check_parenthesis(str))
		return (NULL);
	head = NULL;
	tmp = NULL;
	in_quote = NONE;
	i = 0;
	while (str[i])
	{
		if (in_quote == NONE)
		{
			if (is_double_operator(str[i]) && str[i] == str_last_c(tmp)
				&& ft_strlen(tmp) == 1)
			{
				tmp = str_append_char(tmp, str[i]);
				if (!tmp)
					return (tkn_free(head), NULL);
			}
			else if (tmp && (is_operator(str_last_c(tmp))
				|| is_operator(str[i]) || is_space(str[i])))
			{
				head = token_delimiter(&head, &tmp, str[i]);
				if (!head)
					return (NULL);
			}
			else
			{
				tmp = str_append_char(tmp, str[i]);
				if (!tmp)
					return (tkn_free(head), NULL);
				if (str[i] == '\'')
					in_quote = SINGLE;
				if (str[i] == '"')
					in_quote = DOUBLE;
			}
		}
		else if (in_quote == SINGLE)
		{
			tmp = str_append_char(tmp, str[i]);
			if (!tmp)
				return (tkn_free(head), NULL);
			if (str[i] == '\'')
				in_quote = NONE;
		}
		else if (in_quote == DOUBLE)
		{
			tmp = str_append_char(tmp, str[i]);
			if (!tmp)
				return (tkn_free(head), NULL);
			if (str[i] == '"')
				in_quote = NONE;
		}
		i++;
	}
	return (head);
}
