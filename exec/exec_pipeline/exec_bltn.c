#include "minishell.h"

static int	get_ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	exec_bltn(t_exec *pipeline, t_exdata *exdata)
{
	if (!ft_strncmp(str, "cd", 3))
		return (fd_cd(exdata, get_ac(pipeline->args), pipeline->args));
	if (!ft_strncmp(str, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(str, "env", 4))
		return (ENV);
	if (!ft_strncmp(str, "exit", 5))
		return (EXIT);
	if (!ft_strncmp(str, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(str, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(str, "unset", 6))
		return (UNSET);
}

static void	nullinit_tmp(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

int	forkless_bltn(t_exec *pipeline, t_exdata *exdata)
{
	int	tmpin;
	int	tmpout;
	int	ret;

	nullinit_tmp(&tmpin, &tmpout)
	if (pipeline->redins)
		tmpin = dup(STDIN_FILENO);
	if (pipeline->redouts)
		tmpout = dup(STDOUT_FILENO);
	ret = handle_redirs(pipeline);
	if (ret)
		ret = exec_bltn(pipeline, exdata);
	if (tmpin)
	{
		if (dup2(tmpin, STDIN_FILENO) == -1)
			return (close(tmpin), puterrno(DUP_ERR), 0);
		close(tmpin);
	}
	if (tmpout)
	{
		if (dup2(tmpout, STDOUT_FILENO) == -1)
			return (close(tmpout), puterrno(DUP_ERR), 0);
		close(tmpout);
	}
	return (ret);
}
