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

static int	init_stuff(char **src, char **add, char ***res, int	*size)
{
	if (!add)
		return (free_split(src), 0);
	*size = get_ac(src) + get_ac(add);
	if (get_ac(src) > 0 && get_ac(add) > 0)
		(*size)--;
	*res = malloc(sizeof(char *) * (*size + 1));
	if (!*res)
		return (free_split(src), puterr(MLC_ERR), 0);
	return (1);
}

char	**split_merge(char **src, char **add)
{
	char	**res;
	int		size;
	int		i;
	int		j;

	if (!init_stuff(src, add, &res, &size))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < get_ac(src))
		res[i++] = src[j];
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
