#include "minishell"

t_tkn	*tkn_new(char *str, t_type type)
{
	t_tkn	*new;

	new = malloc(sizeof(t_tkn));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	tkn_append(t_tkn *prev, t_tkn *next)
{
	prev->next = next;
	next->prev = prev;
}

t_tkn	*get_token_word(char *str)
{

}
