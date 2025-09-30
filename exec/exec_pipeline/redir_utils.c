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

char	*str_append_str_redir(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!s1 || !s2)
	{
		if (s1)
			return (free(s1), NULL);
		return (s2);
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

void	null_init_redir(int *i, t_quote *quote, char **res, char **tmp)
{
	*i = 0;
	*quote = NONE;
	*res = NULL;
	*tmp = NULL;
}

int	expappend(t_exdata *exdata, char **tmp, char **res, int mode)
{
	if (mode == 1)
		*tmp = ft_expand(exdata, *tmp);
	*res = str_append_str_redir(*res, *tmp);
	*tmp = NULL;
	if (!*res)
		return (0);
	return (1);
}

int	handle_when_quote(t_redir_data *dt, t_exdata *exdata, char *str)
{
	if (dt->tmp && dt->quote != SINGLE)
	{
		if (!expappend(exdata, &dt->tmp, &dt->res, 1))
			return (free(str), 0);
	}
	else if (dt->tmp)
		if (!expappend(exdata, &dt->tmp, &dt->res, 0))
			return (free(str), 0);
	update_quote(str, &dt->quote, dt->i);
	return (1);
}
