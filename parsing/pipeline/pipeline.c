#include "minishell.h"

static void	sub_parse_red(t_tkn **full, t_tkn **red, t_tkn *tmp)
{
	t_tkn	*word;

	word = tmp->next;
	if (tmp->prev)
	{
		tmp->prev->next = word->next;
		if (word->next)
			word->next->prev = tmp->prev;
	}
	if (!tmp->prev || tmp == *full)
	{
		if (!tmp->prev && word->next)
			word->next->prev = NULL;
		*full = word->next;
	}
	tkn_append(red, tmp);
	tkn_append(red, word);
}

static void	sub_parse_here_doc(t_tkn **full, t_tkn **red, t_tkn *tmp)
{
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	if (!tmp->prev || tmp == *full)
	{
		if (!tmp->prev && tmp->next)
			tmp->next->prev = NULL;
		*full = tmp->next;
	}
	tkn_append(red, tmp);
}

static void	parse_reds(t_tkn **head, t_tkn **redin, t_tkn **redout)
{
	t_tkn	*tmp;
	t_tkn	*next;

	tmp = *head;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_IN)
		{
			next = tmp->next->next;
			sub_parse_red(head, redin, tmp);
		}
		else if (tmp->type == HEREDOC)
		{
			next = tmp->next;
			sub_parse_here_doc(head, redin, tmp);
		}
		else if (tmp->type == RED_OUT || tmp->type == APP_OUT)
		{
			next = tmp->next->next;
			sub_parse_red(head, redout, tmp);
		}
		else
			next = tmp->next;
		tmp = next;
	}
}

static char	**parse_args(t_tkn *head)
{
	t_tkn	*tmp;
	char	**args;
	int		i;

	i = 1;
	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * i);
	if (!args)
		return (puterr(MLC_ERR), NULL);
	i = 0;
	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		args[i] = tmp->str;
		tmp->str = NULL;
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_exec	*pipeline_builder(t_tkn **tkn_head, t_exec *prev)
{
	t_exec	*cmd_head;
	t_tkn	*fake_head;

	cmd_head = exec_new();
	if (!cmd_head)
		return (NULL);
	cmd_head->prev = prev;
	parse_reds(tkn_head, &cmd_head->redin, &cmd_head->redout);
	if (*tkn_head && (*tkn_head)->type != PIPE)
	{
		cmd_head->args = parse_args(*tkn_head);
		if (!cmd_head->args)
			return (exec_free(cmd_head), tkn_free(*tkn_head), NULL);
	}
	else
		cmd_head->args = NULL;
	fake_head = get_next_pipe(*tkn_head);
	if (fake_head)
	{
		cmd_head->next = pipeline_builder(&fake_head, cmd_head);
		if (!cmd_head->next)
			return (exec_free(cmd_head), tkn_free(*tkn_head), NULL);
	}
	return (cmd_head);
}
