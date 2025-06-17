#include "minishell.h"

char	*get_word(char *str, int *i)
{
	char	*word;
	int		single_quotes;
	int		double_quotes;

	*i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[*i] && (!is_meta(&(str[*i])) || single_quotes || double_quotes))
	{
		if (!double_quotes && str[*i] = '\'')
			single_quotes ^= 1;
		if (!single_quotes && str[*i] = '"')
			double_quotes ^= 1;
		(*i)++;
	}
	word = ft_strndup(str, *i);
	if (!word)
		return (NULL);
	return (word);
}

t_tkn	*get_token_redir(char *str, int *i)
{
	t_tkn	new;

	new = tkn_new()
	if (str[i++] == <)
	{
		if (str[i])
		{}

	}
}

t_tkn	*get_token_ctrl(char *str, int *i)
{

}

t_tkn	*get_token_word(char *str, int *i)
{

}

t_tkn	*get_token(t_tkn tokens, char *str, int *i)
{
	t_tkn	tmp;

	*i = 0;
	if (is_redir(str[0]))
		tmp = get_token_redir(str, i);
	else if(is_control(str))
		tmp = get_token_ctrl(str, i);
	else
		tmp = get_token_word(str, i);
	if (!tmp)
		return (tkn_free(tokens), NULL);
	if (!tokens)
		return (tmp);
	tkn_append(tokens, tmp);
	return (tokens);
}
