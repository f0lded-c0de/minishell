#include "minishell"

int	is_meta(char *str)
{
	if (str[0] == ' ' || str[0] == '\t' || str[0] == '\v' || str[0] == '\n'
		|| str[0] == '<' || str[0] == '(' || str[0] == ')' || str[0] == '>'
		|| str[0] == '|' || (str[0] == '&' && str[1] == '&'))
		return (1);
	return (0);
}

int	is_ctrl(char *str)
{
	if (str[0] == '|' || (str[0] == '&' && str[1] == '&')
		|| str[0] == '(' || str[0] == ')')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
