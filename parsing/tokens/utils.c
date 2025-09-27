#include "minishell.h"

t_tkn	*tkn_new(char *str)
{
	t_tkn	*new;

	new = malloc(sizeof(t_tkn));
	if (!new)
		return (puterr(MLC_ERR), NULL);
	new->str = str;
	new->type = -1;
	new->hd_fd = -1;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	tkn_append(t_tkn **start, t_tkn *add)
{
	t_tkn	*tmp;

	if (*start)
	{
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
		add->prev = tmp;
		add->next = NULL;
	}
	else
		*start = add;
}

void	tkn_rm_next(t_tkn *tkn)
{
	t_tkn	*tmp;

	if (tkn)
	{
		tmp = tkn->next;
		if (tmp)
		{
			tkn->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tkn;
			if (tmp->str)
				free(tmp->str);
			free(tmp);
		}
	}
}

void	tkn_rm(t_tkn *tkn)
{
	if (tkn)
	{
		if (tkn->next)
			tkn->next->prev = tkn->prev;
		if (tkn->prev)
			tkn->prev->next = tkn->next;
		if (tkn->str)
			free(tkn->str);
		free(tkn);
	}
}

void	tkn_free(t_tkn *tokens)
{
	t_tkn	*next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->str)
			free(tokens->str);
		if (tokens->type == HEREDOC && tokens->hd_fd != -1)
			close(tokens->hd_fd);
		free(tokens);
		tokens = next;
	}
}
