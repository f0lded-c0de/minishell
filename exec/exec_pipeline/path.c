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

static char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*check_path(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int	is_it_a_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			if (!str[i + 1])
				return (-1);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	no_such_file(void)
{
	if (!ft_strncmp("No such file or directory", strerror(errno), 25))
		return (1);
	return (0);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char		*path_env;
	char		**paths;
	char		*path;
	struct stat	st;

	if (!cmd || !*cmd)
		return (NULL);
	if ((cmd[0] == '/' && !cmd[1])
		|| (cmd[0] == '.' && cmd[1] == '/' && !cmd[2]))
	{
		g_status = 126;
		return (puterrargerr(SH_ERR, cmd, DIR_ERR), NULL);
	}
	if (cmd[0] == '.' && (!cmd[1] || (cmd[1] == '.' && !cmd[2])))
	{
		g_status = 127;
		return (puterrarg(PAT_ERR, cmd), NULL);
	}
	path_env = find_path_env(envp);
	if (path_env)
	{
		paths = ft_split(path_env, ':');
		if (!paths)
			return (NULL);
		path = check_path(paths, cmd);
		free_split(paths);
		if (path)
			return (path);
	}
	if (!path_env || is_it_a_path(cmd))
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			stat(cmd, &st);
			if (!S_ISDIR(st.st_mode))
				return (ft_strdup(cmd));
			g_status = 126;
			return (puterrargerr(SH_ERR, cmd, DIR_ERR), NULL);
		}
		if (no_such_file())
			g_status = 127;
		else
			g_status = 126;
		return (puterrargno(SH_ERR, cmd), NULL);
	}
	g_status = 127;
	return (puterrarg(PAT_ERR, cmd), NULL);
}
