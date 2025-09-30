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

static char	*unquote_redir(t_exdata *exdata, char *str)
{
	t_redir_data	dt;

	null_init_redir(&dt.i, &dt.quote, &dt.res, &dt.tmp);
	while (str[dt.i])
	{
		if ((str[dt.i] == '"' && dt.quote != SINGLE)
			|| (str[dt.i] == '\'' && dt.quote != DOUBLE))
		{
			if (!handle_when_quote(&dt, exdata, str))
				return (NULL);
		}
		else
		{
			dt.tmp = str_append_char(dt.tmp, str[dt.i]);
			if (!dt.tmp)
				return (free(dt.res), free(str), NULL);
		}
		dt.i++;
	}
	if (dt.tmp)
	{
		dt.tmp = ft_expand(exdata, dt.tmp);
		dt.res = str_append_str_redir(dt.res, dt.tmp);
	}
	return (free(str), dt.res);
}

static int	handle_redouts(t_tkn *redouts, t_exdata *exdata)
{
	int	fd;

	fd = 0;
	while (redouts)
	{
		if (fd)
			close(fd);
		redouts->next->str = unquote_redir(exdata, redouts->next->str);
		if (redouts->type == RED_OUT)
		{
			fd = open(redouts->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (puterrargno(SH_ERR, redouts->next->str), -1);
			redouts = redouts->next->next;
		}
		else if (redouts->type == APP_OUT)
		{
			fd = open(redouts->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (puterrargno(SH_ERR, redouts->next->str), -1);
			redouts = redouts->next->next;
		}
	}
	return (fd);
}

static int	handle_redins(t_tkn *redins, t_exdata *exdata)
{
	int	fd;

	fd = 0;
	while (redins)
	{
		if (fd)
			close(fd);
		if (redins->type == RED_IN)
			redins->next->str = unquote_redir(exdata, redins->next->str);
		if (redins->type == RED_IN)
		{
			fd = open(redins->next->str, O_RDONLY);
			if (fd == -1)
				return (puterrargno(SH_ERR, redins->next->str), -1);
			redins = redins->next->next;
		}
		else if (redins->type == HEREDOC)
		{
			fd = redins->hd_fd;
			redins = redins->next;
		}
	}
	return (fd);
}

int	handle_redirs(t_exec *pipeline, t_exdata *exdata)
{
	int	fd_in;
	int	fd_out;

	if (pipeline->redin)
	{
		fd_in = handle_redins(pipeline->redin, exdata);
		if (fd_in == -1)
			return (0);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (close(fd_in), puterrno(DUP_ERR), 0);
		close(fd_in);
	}
	if (pipeline->redout)
	{
		fd_out = handle_redouts(pipeline->redout, exdata);
		if (fd_out == -1)
			return (0);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (close(fd_out), puterrno(DUP_ERR), 0);
		close(fd_out);
	}
	return (1);
}
