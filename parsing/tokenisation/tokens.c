#include "minishell"

t_tkn	*tkn_new(char *str, t_type type)
{
	t_tkn	*new;

	new = malloc(sizeof(t_tkn));
	if (!new)
		return (puterr(MLC_ERR), NULL);
	new->str = str;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	tkn_append(t_tkn *start, t_tkn *new)
{
	t_tkn	tmp;

	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	tkn_free(t_tkn *tokens)
{
	t_tkn	next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->str && tokens->str[0])
			free(tokens->str);
		free(tokens);
		tokens = next;
	}
}
