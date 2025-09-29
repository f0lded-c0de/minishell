#include "minishell.h"

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

// static char	*split_to_str(char **split)
// {
// 	char	*res;
// 	int		size;
// 	int		i;
// 	int		j;
// 	int		k;
//
// 	size = 0;
// 	k = -1;
// 	while (split[++k])
// 		size += ft_strlen(split[k]);
// 	res = malloc(sizeof(char) * (size + 1));
// 	if (!res)
// 		return (puterr(MLC_ERR), free_split(split), NULL);
// 	i = 0;
// 	k = -1;
// 	while (split[++k])
// 	{
// 		j = -1;
// 		while (split[k][++j])
// 			res[i++] = split[k][j];
// 	}
// 	res[i] = '\0';
// 	free_split(split);
// 	return (res);
// }

static char	**unquote_arg(char **env, char *str)
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
				tmp = ft_expand(env, tmp);
				if (quote == NONE)
					tmps = ft_split(tmp, ' ');
				else
					tmps = ft_split(tmp, '\0');
				free(tmp);
				tmp = NULL;
				if (!tmps)
					return (free_split(res), puterr(MLC_ERR), NULL);
				res = split_append(res, tmps);
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
				res = split_append(res, tmps);
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
		tmp = ft_expand(env, tmp);
		res = split_append(res, ft_split(tmp, ' '));
		if (tmp)
			free(tmp);
	}
	return (res);
}

char	**unquote(char **env, char **args)
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
		tmp = unquote_arg(env, args[i]);
		res = split_append(res, tmp);
		if (!res)
			break ;
		i++;
	}
	free_split(args);
	return (res);
}
