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

static void	frexit(t_exec *pl, t_exdata *ex, int pipe[2], int fd_in)
{
	if (pipe && pipe[0] != -1)
		close(pipe[0]);
	if (pipe && pipe[1] != -1)
		close(pipe[1]);
	if (fd_in != -1)
		close(fd_in);
	exec_free(pl);
	free_exdata(ex);
	exit(EXIT_FAILURE);
}

int	brexit(t_exec *pipeline, t_exdata *exdata, int i)
{
	exec_free(pipeline);
	free_exdata(exdata);
	exit(i);
}

void	child_signal(int sig)
{
	g_status = sig;
	if (sig == SIGINT)
	{
		puterr("");
		return ;
	}
	if (sig == SIGQUIT)
	{
		puterr("Quit (core dumped)");
		return ;
	}
}

void	child_setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = child_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_child(t_exec *pipeline, t_exdata *exdata, int pipe[2], int fd_in)
{
	if (pipe[1] != -1)
	{
		close(pipe[0]);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
		{
			puterrno(DUP_ERR);
			frexit(pipeline, exdata, pipe, fd_in);
		}
		close(pipe[1]);
	}
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			puterrno(DUP_ERR);
			frexit(pipeline, exdata, pipe, fd_in);
		}
		close(fd_in);
	}
	if (!handle_redirs(pipeline, exdata))
		frexit(pipeline, exdata, NULL, -1);
	if (pipeline->args && is_bltn(pipeline->args[0]))
		brexit(pipeline, exdata, exec_bltn(pipeline, exdata));
	else
		exec_cmd(pipeline, exdata);
}
