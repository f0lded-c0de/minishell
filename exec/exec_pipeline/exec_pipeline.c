#include "minishell.h"

int	forkless_bltn(t_exec *pipeline, t_exdata *exdata)
{
	int	tmpin;
	int	tmpout;
	int	ret;

	tmpin = 0;
	tmpout = 0;
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

int	exec_pipeline(t_exec *pipeline, t_exdata *exdata)
{
	if (!pipeline->next && is_bltn(pipeline->args[0]))
		return (forkless_bltn(pipeline, exdata));
	else
	{
	}
}
