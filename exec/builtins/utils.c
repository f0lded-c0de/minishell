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

static int	update_oldpwd(t_exdata *shell)
{
	int	i;

	if (!shell->pwd)
		return (0);
	if (shell->oldpwd)
		free(shell->oldpwd);
	shell->oldpwd = shell->pwd;
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->env[i])
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin("OLDPWD=", shell->oldpwd);
	}
	return (0);
}

static int	update_pwd(t_exdata *shell, char *cwd)
{
	int	i;

	shell->pwd = ft_strdup(cwd);
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "PWD=", 4) != 0)
		i++;
	if (shell->env[i])
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin("PWD=", shell->pwd);
	}
	return (0);
}

int	update_pwd_env(t_exdata *shell)
{
	char	buffer[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buffer, PATH_MAX);
	if (!cwd)
		return (1);
	update_oldpwd(shell);
	update_pwd(shell, cwd);
	return (0);
}

int	valid_varname(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A'
				&& name[0] <= 'Z') || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A'
					&& name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

unsigned long long	ft_atoull(const char *str)
{
	int					i;
	unsigned long long	n;
	unsigned long long	dest;

	i = 0;
	n = 1;
	dest = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = n * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		dest = ((dest * 10) + (str[i] - '0'));
		i++;
	}
	return (((dest * n) % 256 + 256) % 256);
}
