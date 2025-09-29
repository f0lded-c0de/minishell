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

static int	brexit(t_exec *pipeline, t_exdata *exdata, int i)
{
	exec_free(pipeline);
	free_exdata(exdata);
	exit(i);
}

static void	child_signal(int sig)
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

static void	child_setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = child_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_child(t_exec *pipeline, t_exdata *exdata, int pipe[2], int fd_in)
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

int	exec_pipeline(t_exec *pipeline, t_exdata *exdata)
{
	int	pipe_fd[2];
	int	fd_in;
	int	cmd_count;
	int	i;
	int	status;

	fd_in = -1;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	i = 0;
	status = 0;
	cmd_count = get_cmd_count(pipeline);
	exdata->pid = malloc(sizeof(int) * cmd_count);
	if (!exdata->pid)
		return (puterr(MLC_ERR), 1);
	if (!pipeline->next && pipeline->args && is_bltn(pipeline->args[0]))
		return (forkless_bltn(pipeline, exdata));
	else
	{
		while (i < cmd_count)
		{
			if (pipeline->next)
			{
				if (pipe(pipe_fd) == -1)
				{
					puterrno(PIP_ERR);
					break ;
				}
			}
			child_setup_signal();
			exdata->pid[i] = fork();
			if (exdata->pid[i] == -1)
			{
				puterrno(FRK_ERR);
				break ;
			}
			if (exdata->pid[i] == 0)
				handle_child(pipeline, exdata, pipe_fd, fd_in);
			if (fd_in != -1)
			{
				close(fd_in);
				fd_in = -1;
			}
			if (pipeline->next)
			{
				fd_in = pipe_fd[0];
				close(pipe_fd[1]);
				pipe_fd[0] = -1;
				pipe_fd[1] = -1;
			}
			pipeline = pipeline->next;
			i++;
		}
		i = -1;
		while (++i < cmd_count)
			waitpid(exdata->pid[i], &status, 0);
		setup_signal();
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 127);
		else if (WIFSTOPPED(status))
			return (WSTOPSIG(status) + 127);
	}
	return (-1);
}
