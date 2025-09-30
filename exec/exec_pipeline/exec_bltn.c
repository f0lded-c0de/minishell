#include "minishell.h"

int	get_ac(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

int	exec_bltn(t_exec *pipeline, t_exdata *exdata)
{
	char **args;

	pipeline->args = unquote(exdata, pipeline->args);
	if (!pipeline->args)
		return (1);
	if (!ft_strncmp(pipeline->args[0], "cd", 3))
		return (ft_cd(exdata, get_ac(pipeline->args), pipeline->args));
	if (!ft_strncmp(pipeline->args[0], "echo", 5))
		return (ft_echo(&pipeline->args[1]));
	if (!ft_strncmp(pipeline->args[0], "env", 4))
		return (ft_env(exdata->env));
	if (!ft_strncmp(pipeline->args[0], "exit", 5))
	{
		args = pipeline->args;
		pipeline->args = NULL;
		return (ft_exit(get_ac(args), args, pipeline, exdata));
	}
	if (!ft_strncmp(pipeline->args[0], "export", 7))
		return (ft_export(exdata, pipeline->args));
	if (!ft_strncmp(pipeline->args[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(pipeline->args[0], "unset", 6))
		return (ft_unset(exdata, pipeline->args));
	return (puterr("Wtf happened here???"), 1);
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

	nullinit_tmp(&tmpin, &tmpout);
	if (pipeline->redin)
		tmpin = dup(STDIN_FILENO);
	if (pipeline->redout)
		tmpout = dup(STDOUT_FILENO);
	ret = handle_redirs(pipeline, exdata);
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
