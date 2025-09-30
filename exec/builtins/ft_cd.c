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

static char	*get_home_dir(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_target_dir(t_exdata *shell, int ac, char **args)
{
	char	*home;

	if (ac == 1)
	{
		home = get_home_dir(shell->env);
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	else if (ac == 2 && ft_strncmp(args[1], "-", 1) == 0)
	{
		if (!shell->oldpwd)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putendl_fd(shell->oldpwd, 1);
		return (shell->oldpwd);
	}
	return (args[1]);
}

int	ft_cd(t_exdata *shell, int ac, char **args)
{
	char	*target_dir;

	if (ac > 2)
		return (puterr(CD_ARGS_ERR), 1);
	target_dir = get_target_dir(shell, ac, args);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (update_pwd_env(shell));
}
