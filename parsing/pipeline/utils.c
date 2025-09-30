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

t_exec	*exec_new(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (puterr(MLC_ERR), NULL);
	new->args = NULL;
	new->redin = NULL;
	new->redout = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	exec_free(t_exec *cmd)
{
	t_exec	*tmp;

	while (cmd && cmd->prev)
		cmd = cmd->prev;
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
	if (!head)
		return (NULL);
	else
		return (head->next);
}
