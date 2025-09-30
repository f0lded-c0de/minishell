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

void	null_init_tokeniser(t_tkn **head, char **tmp, t_quote *quote, int *i)
{
	*head = NULL;
	*tmp = NULL;
	*quote = NONE;
	*i = -1;
}

int	sub_parse_char_unq(t_tkn **head, char **tmp, char c, t_quote *quote)
{
	*head = token_delimiter(head, tmp, c);
	if (!*head)
		return (0);
	if (c == '\'')
		*quote = SINGLE;
	if (c == '"')
		*quote = DOUBLE;
	return (1);
}
