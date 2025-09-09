#include "minishell.h"

static char	*parse_quote(char *str, char *dst, t_delim_status *delim)
{
	char	*tmp;

	if (delim->quote == NONE)
	{
		if (str[delim->index] == '\'')
			delim->quote = SINGLE;
		else if (str[delim->index] == '"')
			delim->quote = DOUBLE;
	}
	else
		delim->quote = NONE;
	if (delim->start_word != -1)
	{
		str[delim->index] = '\0';
		tmp = ft_strjoin(dst, &(str[delim->start_word]));
		delim->start_word = -1;
		free(dst);
	}
	else
		tmp = dst;
	return (tmp);
}

static char *parse_char(char *str, char *dst, t_delim_status *delim)
{
	if ((str[delim->index] != '\'' && str[delim->index] != '"')
			|| (str[delim->index] == '\'' && delim->quote == DOUBLE)
			|| (str[delim->index] == '"' && delim->quote == SINGLE))
	{
		if (delim->start_word == -1)
			delim->start_word = delim->index;
		return (dst);
	}
		else
			return (parse_quote(str, dst, delim));
}

char	*get_delim(char *str)
{
	char			*dst;
	char			*tmp;
	t_delim_status	delim;

	dst = malloc(sizeof(char));
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	delim.index = 0;
	delim.start_word = -1;
	delim.quote = NONE;
	while (str[delim.index])
	{
		dst = parse_char(str, dst, &delim);
		if (!dst)
			return (NULL);
		delim.index++;
	}
	if (delim.start_word != -1)
	{
		tmp = ft_strjoin(dst, &(str[delim.start_word]));
		free(dst);
		dst = tmp;
	}
	return (dst);
}
