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

static int	expand_n_splerge(t_exdata *exdata, t_quote_data *dt)
{
	dt->tmp = ft_expand(exdata, dt->tmp);
	if (!split_n_merge(&dt->tmp, &dt->res, &dt->tmps, dt->quote))
		return (0);
	return (1);
}

static char	**unquote_arg(t_exdata *exdata, char *str)
{
	t_quote_data	dt;

	null_init_quote(&dt.i, &dt.quote, &dt.res, &dt.tmp);
	while (str[dt.i])
	{
		if ((str[dt.i] == '"' && dt.quote != SINGLE)
			|| (str[dt.i] == '\'' && dt.quote != DOUBLE))
		{
			if (dt.tmp && dt.quote != SINGLE)
			{
				if (!expand_n_splerge(exdata, &dt))
					return (NULL);
			}
			else if (dt.tmp)
				if (!split_n_merge(&dt.tmp, &dt.res, &dt.tmps, SINGLE))
					return (NULL);
			update_quote(str, &dt.quote, dt.i);
		}
		else if (!str_append_char_bis(dt.res, &dt.tmp, str, dt.i))
			return (NULL);
		dt.i++;
	}
	if (dt.tmp)
		handle_end(exdata, &dt.res, &dt.tmp);
	return (dt.res);
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
