#include "minishell.h"

static char	*str_append_str(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!s1 || !s2)
	{
		if (s1)
			return (free(s1), NULL);
		return (s2);
	}
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	new = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new)
		return (free(s1), free(s2), puterr(MLC_ERR), NULL);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2 + 1);
	return (free(s1), free(s2), new);
}

static char	*unquote_redir(t_exdata *exdata, char *str)
{
	char	*res;
	char	*tmp;
	int		i;
	t_quote	quote;

	i = 0;
	quote = NONE;
	res = NULL;
	tmp = NULL;
	while (str[i])
	{
		if ((str[i] == '"' && quote != SINGLE)
			|| (str[i] == '\'' && quote != DOUBLE))
		{
			if (tmp && quote != SINGLE)
			{
				tmp = ft_expand(exdata, tmp);
				res = str_append_str(res, tmp);
				tmp = NULL;
				if (!res)
					return (free(str), NULL);
			}
			else if (tmp)
			{
				res = str_append_str(res, tmp);
				tmp = NULL;
				if (!res)
					return (free(str), NULL);
			}
			if (str[i] == '"' && quote == NONE)
				quote = DOUBLE;
			else if (str[i] == '"' && quote == DOUBLE)
				quote = NONE;
			else if (str[i] == '\'' && quote == NONE)
				quote = SINGLE;
			else if (str[i] == '\'' && quote == SINGLE)
				quote = NONE;
		}
		else
		{
			tmp = str_append_char(tmp, str[i]);
			if (!tmp)
				return (free(res), free(str), NULL);
		}
		i++;
	}
	if (tmp)
	{
		tmp = ft_expand(exdata, tmp);
		res = str_append_str(res, tmp);
	}
	return (free(str), res);
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
				return (puterrno(OPN_ERR), -1);
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
