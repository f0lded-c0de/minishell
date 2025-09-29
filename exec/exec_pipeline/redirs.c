#include "minishell.h"

static int	handle_redouts(t_tkn *redouts)
{
	int	fd;

	fd = 0;
	while (redouts)
	{
		if (fd)
			close(fd);
		if (redouts->type == RED_OUT)
		{
			fd = open(redouts->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (puterrno(OPN_ERR), -1);
			redouts = redouts->next->next;
		}
		else if (redouts->type == APP_OUT)
		{
			fd = open(redouts->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (puterrno(OPN_ERR), -1);
			redouts = redouts->next->next;
		}
		else
			redouts = redouts->next;
	}
	return (fd);
}

static int	handle_redins(t_tkn *redins)
{
	int	fd;

	fd = 0;
	while (redins)
	{
		if (fd)
			close(fd);
		if (redins->type == RED_IN)
		{
			fd = open(redins->next->str, O_RDONLY);
			if (fd == -1)
				return (puterrno(OPN_ERR), -1);
			redins = redins->next->next;
		}
		else if (redins->type == HEREDOC)
		{
			fd = redins->hd_fd;
			redins = redins->next;
		}
		else
			redins = redins->next;
	}
	return (fd);
}

int	handle_redirs(t_exec *pipeline)
{
	int	fd_in;
	int	fd_out;

	if (pipeline->redin)
	{
		fd_in = handle_redins(pipeline->redin);
		if (fd_in == -1)
			return (0);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (close(fd_in), puterrno(DUP_ERR), 0);
		close(fd_in);
	}
	if (pipeline->redout)
	{
		fd_out = handle_redouts(pipeline->redout);
		if (fd_out == -1)
			return (0);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (close(fd_out), puterrno(DUP_ERR), 0);
		close(fd_out);
	}
	return (1);
}
