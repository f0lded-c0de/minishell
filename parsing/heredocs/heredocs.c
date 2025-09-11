#include "minishell.h"

static int	handle_here_doc(t_tkn *hd, int expand, char *delim)
{
	char	*input;
	int		fd[2];

	(void)expand;
	if (!delim)
		return (0);
	if (pipe(fd) == -1)
		return (free(delim), puterrno(PIP_ERR), 0);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (free(delim), close_pipes(fd), puterr(HDC_ERR), 0);
		if (!ft_strcmp(input, delim))
			break ;
		/* if (expand) */
		/* 	ft_expand; */
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	free(input);
	free(delim);
	hd->hd_fd = fd[0];
	close(fd[1]);
	return (1);
}

int	parse_here_docs(t_tkn *head)
{
	int	i;
	int	expand;

	while (head)
	{
		if (head->type == HEREDOC)
		{
			i = 0;
			expand = 0;
			while (head->next->str[i])
			{
				if (head->next->str[i] == '\'' || head->next->str[i] == '"')
					expand = 1;
				i++;
			}
			if (!handle_here_doc(head, expand, get_delim(head->next->str)))
				return (0);
			tkn_rm_next(head);
		}
		head = head->next;
	}
	return (1);
}
