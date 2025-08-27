#include "minishell.h"

// pre_check
void	null_init_ints_counters(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int	check_unclosed(char *str)
{
	int	single_count;
	int	double_count;
	int	par_count;
	int	i;

	null_init_ints_counters(&single_count, &double_count, &par_count, &i);
	while (str[i])
	{
		if (str[i] == '\'' && !(double_count % 2))
			single_count++;
		if (str[i] == '"' && !(single_count % 2))
			double_count++;
		if (str[i] == '(' && !(double_count % 2) && !(single_count % 2))
			par_count++;
		if (str[i] == ')' && !(double_count % 2) && !(single_count % 2))
			par_count--;
		i++;
	}
	if ((single_count % 2) || (double_count % 2))
		return (puterr(QUO_ERR), 0);
	if (par_count != 0)
		return (puterr(PAR_ERR), 0);
	return (1);
}

// post_check
void	check_syntax(t_tkn **head)
{
	t_tkn	*tmp;

	tmp = *head;
	while (tmp)
	{
		if ((tmp->type >= PIPE && tmp->type <= AND && (!tmp->next
			|| (tmp->next->type != WORD && tmp->next->type != PAR_OPEN)))
			|| (tmp->type >= PIPE && tmp->type <= AND && (!tmp->prev
			|| (tmp->prev->type != WORD && tmp->prev->type != PAR_CLOSE)))
			|| (tmp->type >= RED_IN && tmp->type <= APP_OUT
			&& (!tmp->prev || tmp->next->type != WORD)))
		{
			puterrarg(TKN_ERR, tmp->str);
			tkn_free(*head);
			*head = NULL;
			tmp = NULL;
		}
		if (tmp)
			tmp = tmp->next;
	}
}
