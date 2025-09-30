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

static int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	free_all(char **args, t_exec *pipeline, t_exdata *exdata)
{
	free_exdata(exdata);
	exec_free(pipeline);
	free_split(args);
}

static void	num_arg_req(char **args, t_exec *pipeline, t_exdata *exdata)
{
	write(2, "exit: numeric argument required\n", 32);
	free_all(args, pipeline, exdata);
	exit(2);
}

int	ft_exit(int ac, char **args, t_exec *pipeline, t_exdata *exdata)
{
	unsigned long long	exit_code;

	exit_code = 0;
	if (ac >= 2)
	{
		if (!ft_strisdigit(args[1]))
			num_arg_req(args, pipeline, exdata);
		exit_code = ft_atoull(args[1]);
		if (exit_code >= LLONG_MAX)
			num_arg_req(args, pipeline, exdata);
		if (ac > 2)
		{
			write(2, "exit: too many arguments\n", 25);
			free_split(args);
			return (1);
		}
		free_all(args, pipeline, exdata);
		exit((int)exit_code);
	}
	free_all(args, pipeline, exdata);
	exit(0);
}
