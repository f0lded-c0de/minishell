/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkbomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:04:43 by bsamzun           #+#    #+#             */
/*   Updated: 2025/03/22 11:50:29 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_question(char *res, int exit_status)
{
	char	*dst;
	char	*tmp;

	tmp = ft_itoa(exit_status);
	if (!tmp)
		return (puterr(MLC_ERR), free(res), NULL);
	dst = ft_strjoin(res, tmp);
	free(res);
	free(tmp);
	if (!dst)
		puterr(MLC_ERR);
	return (dst);
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

static char	*get_value(char **env, char *name)
{
	char	*value;
	int		i;

	if (!env || !env[0])
		return (puterr(ENV_ERR), NULL);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name))
			&& env[i][ft_strlen(name)] == '=')
		{
			value = ft_strdup(&env[i][ft_strlen(name) + 1]);
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

char	*handle_expand(char **env, char *str, char *res, int i[2])
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
