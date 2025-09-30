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

static char	*handle_unexpand(char *str, char *res, int i, int j)
{
	char	*tmp;
	char	*dst;
	int		k;

	tmp = malloc(sizeof(char) * ((j - i) + 1));
	if (!tmp)
		return (puterr(MLC_ERR), free(res), NULL);
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

static void	sub_expand2(t_exdata *exdata, t_expand_data *dt)
{
	dt->expand = 0;
	dt->res = handle_question(dt->res, exdata->exit_status);
	dt->i[0] = dt->i[1] + 1;
}

static int	sub_expand1(t_exdata *exdata, t_expand_data *dt, char *str)
{
	if (dt->expand == 0 && str[dt->i[1]] == '$')
	{
		dt->expand = 1;
		if (dt->i[0] != dt->i[1])
		{
			dt->res = handle_unexpand(str, dt->res, dt->i[0], dt->i[1]);
			if (!dt->res)
				return (0);
			dt->i[0] = dt->i[1];
		}
	}
	else if (dt->expand == 1
		&& dt->i[1] - dt->i[0] == 1 && str[dt->i[1]] == '?')
		sub_expand2(exdata, dt);
	else if (dt->expand == 1 && !is_still_name(str, dt->i))
	{
		if (str[dt->i[1]] != '$')
			dt->expand = 0;
		dt->res = handle_expand(exdata->env, str, dt->res, dt->i);
		if (!dt->res)
			return (puterr(MLC_ERR), 0);
		dt->i[0] = dt->i[1];
	}
	return (1);
}

char	*ft_expand(t_exdata *exdata, char *str)
{
	t_expand_data	dt;

	dt.i[0] = 0;
	dt.i[1] = 0;
	dt.expand = 0;
	dt.res = malloc(sizeof(char));
	if (!dt.res)
		return (puterr(MLC_ERR), NULL);
	dt.res[0] = '\0';
	while (str[dt.i[1]])
	{
		if (!sub_expand1(exdata, &dt, str))
			return (NULL);
		dt.i[1]++;
	}
	if (dt.expand == 0 && dt.i[0] != dt.i[1])
		dt.res = handle_unexpand(str, dt.res, dt.i[0], dt.i[1]);
	else if (dt.expand == 1 && dt.i[0] != dt.i[1])
		dt.res = handle_expand(exdata->env, str, dt.res, dt.i);
	free(str);
	return (dt.res);
}
