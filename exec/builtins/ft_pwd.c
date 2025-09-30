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

int	ft_pwd(void)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	cwd = getcwd(buffer, PATH_MAX);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	if (write(1, cwd, ft_strlen(cwd)) == -1)
		return (1);
	if (write(1, "\n", 1) == -1)
		return (1);
	return (0);
}
