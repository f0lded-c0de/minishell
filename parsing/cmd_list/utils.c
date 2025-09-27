#include "minishell.h"

t_exec	*exec_new(char **args, t_tkn *redin, t_tkn *redout)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (puterr(MLC_ERR), NULL);
	new->args = args;
	new->redin = redin;
	new->redout = redout;
	new->next = NULL;
	return (new);
}

void	exec_free(t_exec *cmd)
{
	t_exec tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->redin)
			tkn_free(cmd->redin);
		if (cmd->redout)
			tkn_free(cmd->redout);
		free(cmd);
		cmd = tmp;
	}
}

t_tkn	*get_next_pipe(t_tkn *head)
{
	while (head && head->type != PIPE)
		head = head->next;
	return (head);
}
