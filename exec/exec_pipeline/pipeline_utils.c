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

int	pipe_and_sig(t_exec *pipeline, int pipe_fd[2])
{
	if (pipeline->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			puterrno(PIP_ERR);
			return (0);
		}
	}
	child_setup_signal();
	return (1);
}

int	fork_and_check(t_exdata *exdata, int i)
{
	exdata->pid[i] = fork();
	if (exdata->pid[i] == -1)
	{
		puterrno(FRK_ERR);
		return (0);
	}
	return (1);
}

int	pipe_and_fork(t_exec *ppl, t_exdata *exdata, int p_fd[2], int i)
{
	if (!pipe_and_sig(ppl, p_fd))
		return (0);
	if (!fork_and_check(exdata, i))
		return (0);
	return (1);
}

void	up_fd_and_go_on(t_exec **pipeline, int p_fd[2], int *fd_in, int *i)
{
	if (*fd_in != -1)
	{
		close(*fd_in);
		*fd_in = -1;
	}
	if ((*pipeline)->next)
	{
		*fd_in = p_fd[0];
		close(p_fd[1]);
		p_fd[0] = -1;
		p_fd[1] = -1;
	}
	*pipeline = (*pipeline)->next;
	*i += 1;
}

int	wait_and_get_stat(t_exdata *exdata, int	*status, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
		waitpid(exdata->pid[i], status, 0);
	setup_signal();
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
		return (WTERMSIG(*status) + 127);
	else if (WIFSTOPPED(*status))
		return (WSTOPSIG(*status) + 127);
	return (-1);
}
