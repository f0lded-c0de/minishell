#include "minishell.h"

static char	*str_append_str(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!s1 || !s2)
	{
		if (s1)
			return (free(s1), NULL);
		if (s2)
			return (free(s2), NULL);
	}
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	new = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new)
		return (free(s1), free(s2), puterr(MLC_ERR), NULL);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2 + 1);
	return (free(s1), free(s2), new);
}

static char	**split_merge(char **src, char **add)
{
	char	**res;
	int		size;
	int		i;
	int		j;

	if (!add)
		return (free_split(src), NULL);
	size = get_ac(src) + get_ac(add);
	if (get_ac(src) > 0 && get_ac(add) > 0)
		size--;
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (free_split(src), puterr(MLC_ERR), NULL);
	i = 0;
	j = -1;
	while (++j < get_ac(src))
	{
		res[i] = src[j];
		i++;
	}
	i--;
	j = 0;
	if (i >= 0 && get_ac(add) > 0)
	{
		res[i] = str_append_str(res[i], add[j++]);
		if (!res[i])
			return (free_split(res), free(src), free_split(add), NULL);
	}
	while (++i < size)
		res[i] = add[j++];
	res[i] = NULL;
	return (free(src), free(add), res);
}

static char	**unquote_arg(t_exdata *exdata, char *str)
{
	char	**res;
	char	**tmps;
	char	*tmp;
	int		i;
	t_quote	quote;

	i = 0;
	quote = NONE;
	res = NULL;
	tmp = NULL;
	while (str[i])
	{
		if ((str[i] == '"' && quote != SINGLE)
			|| (str[i] == '\'' && quote != DOUBLE))
		{
			if (tmp && quote != SINGLE)
			{
				tmp = ft_expand(exdata, tmp);
				if (quote == NONE)
					tmps = ft_split(tmp, ' ');
				else
					tmps = ft_split(tmp, '\0');
				free(tmp);
				tmp = NULL;
				if (!tmps)
					return (free_split(res), puterr(MLC_ERR), NULL);
				res = split_merge(res, tmps);
				if (!res)
					return (puterr(MLC_ERR), NULL);
			}
			else if (tmp)
			{
				tmps = ft_split(tmp, '\0');
				free(tmp);
				tmp = NULL;
				if (!tmps)
					return (free_split(res), puterr(MLC_ERR), NULL);
				res = split_merge(res, tmps);
				if (!res)
					return (puterr(MLC_ERR), NULL);
			}
			if (str[i] == '"' && quote == NONE)
				quote = DOUBLE;
			else if (str[i] == '"' && quote == DOUBLE)
				quote = NONE;
			else if (str[i] == '\'' && quote == NONE)
				quote = SINGLE;
			else if (str[i] == '\'' && quote == SINGLE)
				quote = NONE;
		}
		else
		{
			tmp = str_append_char(tmp, str[i]);
			if (!tmp)
				return (free_split(res), NULL);
		}
		i++;
	}
	if (tmp)
	{
		tmp = ft_expand(exdata, tmp);
		res = split_merge(res, ft_split(tmp, ' '));
		if (tmp)
			free(tmp);
	}
	return (res);
}

static char	**split_append(char **src, char **add)
{
	char	**res;
	int		i;
	int		j;

	if (!add)
		return (free_split(src), NULL);
	res = malloc(sizeof(char *) * (get_ac(src) + get_ac(add) + 1));
	if (!res)
		return (free_split(src), puterr(MLC_ERR), NULL);
	i = 0;
	j = -1;
	while (++j < get_ac(src))
	{
		res[i] = src[j];
		i++;
	}
	j = -1;
	while (++j < get_ac(add))
	{
		res[i] = add[j];
		i++;
	}
	res[i] = NULL;
	return (free(src), free(add), res);
}

char	**unquote(t_exdata *exdata, char **args)
{
	char	**res;
	char	**tmp;
	int		i;

	i = 0;
	res = NULL;
	if (!args)
		return (NULL);
	while (args[i])
	{
		tmp = unquote_arg(exdata, args[i]);
		res = split_append(res, tmp);
		if (!res)
			break ;
		i++;
	}
	free_split(args);
	return (res);
}
