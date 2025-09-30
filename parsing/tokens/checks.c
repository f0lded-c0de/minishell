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

// pre_check
void	null_init_ints_counters(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int	check_unclosed(char *str)
{
	int	single_count;
	int	double_count;
	int	i;

	null_init_ints_counters(&single_count, &double_count, &i);
	while (str[i])
	{
		if (str[i] == '\'' && !(double_count % 2))
			single_count++;
		if (str[i] == '"' && !(single_count % 2))
			double_count++;
		i++;
	}
	if ((single_count % 2) || (double_count % 2))
		return (puterr(QUO_ERR), 0);
	return (1);
}

// post_check
void	check_syntax(t_tkn **head)
{
	t_tkn	*tmp;

	tmp = *head;
	while (tmp)
	{
		if ((tmp->type == PIPE && (!tmp->next || tmp->next->type == PIPE
			|| !tmp->prev || tmp->prev->type != WORD))
			|| (tmp->type >= RED_IN && tmp->type <= APP_OUT
			&& (!tmp->next || tmp->next->type != WORD)))
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
