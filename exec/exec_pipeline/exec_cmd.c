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

static void	frexit(t_exec *pipeline, t_exdata *exdata)
{
	exec_free(pipeline);
	free_exdata(exdata);
	exit(g_status);
}

void	exec_cmd(t_exec *pipeline, t_exdata *exdata)
{
	char	**args;
	char	**env;
	char	*path;

	g_status = 0;
	if (!pipeline->args)
		frexit(pipeline, exdata);
	pipeline->args = unquote(exdata, pipeline->args);
	if (!pipeline->args)
		frexit(pipeline, exdata);
	path = get_cmd_path(pipeline->args[0], exdata->env);
	if (!path)
		frexit(pipeline, exdata);
	args = pipeline->args;
	env = exdata->env;
	pipeline->args = NULL;
	exdata->env = NULL;
	free_exdata(exdata);
	exec_free(pipeline);
	execve(path, args, env);
	free_split(args);
	free_split(env);
	free(path);
	puterrno(EXV_ERR);
	exit(EXIT_FAILURE);
}
