#include "minishell.h"

static char	*handle_unexpand(char *str, char *res, int i, int j)
{
	char	*tmp;
	char	*dst;
	int		k;

	tmp = malloc(sizeof(char) * ((i - j) + 1));
	if (!tmp)
		return (puterr(MLC_ERR), NULL);
	k = -1;
	while ((++k + i) < j)
		tmp[k] = str[i + k];
	tmp[k] = '\0';
	dst = ft_strjoin(res, tmp);
	free(res);
	free(tmp);
	if (!dst)
		puterr(MLC_ERR);
	return (dst);
}

/* static char	*handle_question(char *str, char *res, int i, int j) */
/* { */
/**/
/* } */

static int	is_still_name(char *str, int i[2])
{
	if (i[1] - i[0] == 1 && str[i[1]] >= '0' && str[i[1]] <= '9')
		return (0);
	if (str[i[1]] < '0')
		return (0);
	if (str[i[1]] > '9' && str[i[1]] < 'A')
		return (0);
	if (str[i[1]] > 'Z' && str[i[1]] < 'a' && str[i[1]] != '_')
		return (0);
	if (str[i[1]] > 'z')
		return (0);
	return (1);
}

static char	*get_name(char *str, int i[2])
{
	char	*name;
	int		size;
	int		j;

	size = i[1] - i[0];
	if (i[1] - i[0] > 1)
		size--;
	name = malloc(sizeof(char) * (size + 1));
	if (!name)
		return (puterr(MLC_ERR), NULL);
	name[size] = '\0';
	j = 0;
	while (++j <= size)
		name[size - j] = str[i[1] - j];
	return (name);
}

char	**get_value(char **env, char *name)
{
	char	*value;
	int		i;

	if (!env[0])
		return (puterr(ENV_ERR), NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name))
			&& env[i][ft_strlen(name)] == '=')
		{
			value = ft_strdup(&env[0][ft_strlen(name) + 1]);
			if (!value)
				puterr(MLC_ERR);
			return (value);
		}
		i++;
	}
	value = ft_strdup("");
	if (!value)
		puterr(MLC_ERR);
	return (value);
}

static char	*handle_expand(char **env, char *str, char *res, int i[2])
{
	char	*name;
	char	*value;
	char	*dst;

	name = get_name(str, i);
	if (!name)
		return (NULL);
	value = get_value(env, name);
	if (!value)
		return (free(name), NULL);
	if (i[1] - i[0] == 1)
		dst = ft_strjoin(res, name);
	else
		dst = ft_strjoin(res, value);
	free(name);
	free(value);
	free(res);
	if (!dst)
		puterr(MLC_ERR);
	return (dst);
}

char	*ft_expand(char *str)
{
	char	*res;
	int		expand;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	expand = 0;
	res = malloc(sizeof(char));
	if (!res)
		return (puterr(MLC_ERR), NULL);
	res[0] = '\0';
	while (str[i[1]])
	{
		if (expand == 0 && str[i[1]] == '$')
		{
			expand = 1;
			if (i[0] != i[1])
			{
				res = handle_unexpand(str, res, i[0], i[1]);
				if (!res)
					return (NULL);
				i[0] = i[1];
			}
		}
		/* else if (expand == 1 && i[1] - i[0] == 1 && str[i[1]] == '?') */
		/* { */
		/* 	expand = 0; */
		/* 	res = handle_question(str, res, whatever_the_fuck_we_need_for_that); */
		/* 	i[0] = i[1] + 1; */
		/* } */
		else if (expand == 1 && !is_still_name(str, i))
		{
			expand = 0;
			res = handle_expand(env, str, res, i);
			if (!res)
				return (puterr(MLC_ERR), NULL);
			i[0] = i[1];
		}
		i[1]++;
	}
	free(str);
	return (res);
}
