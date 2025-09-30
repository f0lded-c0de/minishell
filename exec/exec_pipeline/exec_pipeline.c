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

static void	init1(int *fd_in, int pipe_fd[2], int *i, int *status)
{
	*fd_in = -1;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	*i = 0;
	*status = 0;
}

static int	init2(t_exec *pipeline, t_exdata *exdata, int *cmd_count)
{
	*cmd_count = get_cmd_count(pipeline);
	exdata->pid = malloc(sizeof(int) * *cmd_count);
	if (!exdata->pid)
		return (puterr(MLC_ERR), 0);
	return (1);
}

int	exec_pipeline(t_exec *pipeline, t_exdata *exdata)
{
	int	pipe_fd[2];
	int	fd_in;
	int	cmd_count;
	int	i;
	int	status;

	init1(&fd_in, pipe_fd, &i, &status);
	if (!init2(pipeline, exdata, &cmd_count))
		return (1);
	if (!pipeline->next && pipeline->args && is_bltn(pipeline->args[0]))
		return (forkless_bltn(pipeline, exdata));
	else
	{
		while (i < cmd_count)
		{
			if (!pipe_and_fork(pipeline, exdata, pipe_fd, i))
				break ;
			if (exdata->pid[i] == 0)
				handle_child(pipeline, exdata, pipe_fd, fd_in);
			up_fd_and_go_on(&pipeline, pipe_fd, &fd_in, &i);
		}
		return (wait_and_get_stat(exdata, &status, cmd_count));
	}
	return (-1);
}
