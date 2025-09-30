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

static int	print_error(char *var)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	update_env_2(t_exdata *shell, char **new_var, char *var, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_var[j] = shell->env[j];
		j++;
	}
	new_var[i] = ft_strdup(var);
	if (!new_var[i])
	{
		free(new_var);
		return (1);
	}
	new_var[i + 1] = NULL;
	free(shell->env);
	shell->env = new_var;
	return (0);
}

static int	update_env(t_exdata *shell, char *var, char *name)
{
	int		i;
	char	**new_var;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			if (!shell->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	new_var = malloc(sizeof(char *) * (i + 2));
	if (!new_var)
		return (1);
	update_env_2(shell, new_var, var, i);
	return (0);
}

static int	process_variable(t_exdata *shell, char *var)
{
	char	*equals;
	char	*name;
	int		res;

	equals = ft_strchr(var, '=');
	if (!equals)
	{
		if (!valid_varname(var))
			return (print_error(var));
		return (0);
	}
	name = ft_substr(var, 0, (equals - var));
	if (!valid_varname(name))
	{
		free(name);
		return (print_error(var));
	}
	res = update_env(shell, var, name);
	free(name);
	return (res);
}

int	ft_export(t_exdata *shell, char **args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!args || !args[0])
	{
		handle_env(shell->env);
		return (0);
	}
	while (args[i])
	{
		if (process_variable(shell, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
