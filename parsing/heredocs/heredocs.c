#include "minishell.h"

static void	child_setup_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = SIG_DFL;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void	finish_hd(char **env, char *input, char *delim, int fd)
{
	if (input)
		free(input);
	else
		puterrarg(HDC_WRN, delim);
	free(delim);
	close(fd);
	free_split(env);
}

static void	read_hd(char **env, char *delim, int fd[2], int expand)
{
	char	*input;

	close(fd[0]);
	child_setup_signal();
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (!ft_strcmp(input, delim))
			break ;
		if (expand)
			input = ft_expand(env, input);
		if (!input)
		{
			finish_hd(env, input, delim, fd[1]);
			exit(1);
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	finish_hd(env, input, delim, fd[1]);
	exit(0);
}

static int	handle_here_doc(char **env, t_tkn *hd, int expand, char *delim)
{
	int		fd[2];
	int		pid;
	int		status;

	if (!delim)
		return (0);
	if (pipe(fd) == -1)
		return (free(delim), puterrno(PIP_ERR), 0);
	pid = fork();
	if (pid == -1)
		return (free(delim), close_pipes(fd), puterrno(FRK_ERR), 0);
	if (pid == 0)
		read_hd(env, delim, fd, expand);
	close(fd[1]);
	free(delim);
	if (waitpid(pid, &status, 0) == -1)
		return (printf("test lolol\n"), close(fd[0]), puterrno(WPD_ERR), 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_status = SIGINT;
		return (close(fd[0]), 0);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (close(fd[0]), puterr(WTF_ERR), 0);
	hd->hd_fd = fd[0];
	return (1);
}

int	parse_here_docs(char **env, t_tkn *head)
{
	int	i;
	int	expand;

	while (head)
	{
		if (head->type == HEREDOC)
		{
			i = 0;
			expand = 1;
			while (head->next->str[i])
			{
				if (head->next->str[i] == '\'' || head->next->str[i] == '"')
					expand = 0;
				i++;
			}
			if (!handle_here_doc(env, head, expand, get_delim(head->next->str)))
				return (0);
			tkn_rm_next(head);
		}
		head = head->next;
	}
	return (1);
}
