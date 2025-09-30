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

int	split_n_merge(char **tmp, char ***res, char ***tmps, t_quote mode)
{
	if (mode == NONE)
		*tmps = ft_split(*tmp, ' ');
	else
		*tmps = ft_split(*tmp, '\0');
	free(*tmp);
	*tmp = NULL;
	if (!(*tmps))
		return (free_split(*res), puterr(MLC_ERR), 0);
	*res = split_merge(*res, *tmps);
	if (!(*res))
		return (puterr(MLC_ERR), 0);
	return (1);
}

void	update_quote(char *str, t_quote *quote, int i)
{
	if (str[i] == '"' && *quote == NONE)
		*quote = DOUBLE;
	else if (str[i] == '"' && *quote == DOUBLE)
		*quote = NONE;
	else if (str[i] == '\'' && *quote == NONE)
		*quote = SINGLE;
	else if (str[i] == '\'' && *quote == SINGLE)
		*quote = NONE;
}

void	handle_end(t_exdata *exdata, char ***res, char **tmp)
{
	*tmp = ft_expand(exdata, *tmp);
	*res = split_merge(*res, ft_split(*tmp, ' '));
	if (*tmp)
		free(*tmp);
}

int	str_append_char_bis(char **res, char **tmp, char *str, int i)
{
	*tmp = str_append_char(*tmp, str[i]);
	if (!*tmp)
		return (free_split(res), 0);
	return (1);
}

void	null_init_quote(int *i, t_quote *quote, char ***res, char **tmp)
{
	*i = 0;
	*quote = NONE;
	*res = NULL;
	*tmp = NULL;
}
