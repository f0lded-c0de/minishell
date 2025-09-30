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

t_bltn	is_bltn(char *str)
{
	if (!ft_strncmp(str, "cd", 3))
		return (CD);
	if (!ft_strncmp(str, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(str, "env", 4))
		return (ENV);
	if (!ft_strncmp(str, "exit", 5))
		return (EXIT);
	if (!ft_strncmp(str, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(str, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(str, "unset", 6))
		return (UNSET);
	return (NOT_BLTN);
}

int	get_cmd_count(t_exec *pipeline)
{
	int	i;

	i = 0;
	while (pipeline)
	{
		pipeline = pipeline->next;
		i++;
	}
	return (i);
}
