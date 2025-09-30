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

int	no_such_file(void)
{
	if (!ft_strncmp("No such file or directory", strerror(errno), 25))
		return (1);
	return (0);
}

int	get_start(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if ((cmd[0] == '/' && !cmd[1])
		|| (cmd[0] == '.' && cmd[1] == '/' && !cmd[2]))
	{
		g_status = 126;
		return (puterrargerr(SH_ERR, cmd, DIR_ERR), 0);
	}
	if (cmd[0] == '.' && (!cmd[1] || (cmd[1] == '.' && !cmd[2])))
	{
		g_status = 127;
		return (puterrarg(PAT_ERR, cmd), 0);
	}
	return (1);
}

char	*get_mid(char *cmd, t_path_data *dt)
{
	stat(cmd, &dt->st);
	if (!S_ISDIR(dt->st.st_mode))
		return (ft_strdup(cmd));
	g_status = 126;
	return (puterrargerr(SH_ERR, cmd, DIR_ERR), NULL);
}

void	get_end(void)
{
	if (no_such_file())
		g_status = 127;
	else
		g_status = 126;
}
