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

static void	type_assign(t_tkn *token)
{
	if (!is_operator(token->str[0]))
		token->type = WORD;
	else if (!ft_strncmp(token->str, ">>", 3))
		token->type = APP_OUT;
	else if (!ft_strncmp(token->str, "<<", 3))
		token->type = HEREDOC;
	else if (!ft_strncmp(token->str, "<", 2))
		token->type = RED_IN;
	else if (!ft_strncmp(token->str, ">", 2))
		token->type = RED_OUT;
	else if (!ft_strncmp(token->str, "|", 2))
		token->type = PIPE;
}

t_tkn	*token_delimiter(t_tkn **head, char **tmp, char c)
{
	t_tkn	*new;

	new = tkn_new(*tmp);
	if (!new)
		return (tkn_free(*head), free(*tmp), NULL);
	type_assign(new);
	tkn_append(head, new);
	*tmp = NULL;
	if (c && !is_space(c))
		*tmp = str_append_char(*tmp, c);
	return (*head);
}

static int	parse_char_unquote(t_tkn **head, char **tmp, char c, t_quote *quote)
{
	if (is_double_operator(c) && c == str_last_c(*tmp) && ft_strlen(*tmp) == 1)
	{
		*tmp = str_append_char(*tmp, c);
		if (!*tmp)
			return (tkn_free(*head), 0);
	}
	else if (*tmp && (is_operator(str_last_c(*tmp))
			|| is_operator(c) || is_space(c)))
	{
		if (!sub_parse_char_unq(head, tmp, c, quote))
			return (0);
	}
	else if (!is_space(c))
	{
		*tmp = str_append_char(*tmp, c);
		if (!*tmp)
			return (tkn_free(*head), 0);
		if (c == '\'')
			*quote = SINGLE;
		if (c == '"')
			*quote = DOUBLE;
	}
	return (1);
}

static int	parse_char_quote(t_tkn *head, char **tmp, char c, t_quote *quote)
{
	*tmp = str_append_char(*tmp, c);
	if (!*tmp)
		return (tkn_free(head), 0);
	if (*quote == SINGLE && c == '\'')
		*quote = NONE;
	else if (*quote == DOUBLE && c == '"')
		*quote = NONE;
	return (1);
}

t_tkn	*tokeniser(t_maxishell *maxishell, char *str)
{
	t_tkn	*head;
	char	*tmp;
	t_quote	quote;
	int		i;

	if (!str[0] || !check_unclosed(str))
		return (NULL);
	null_init_tokeniser(&head, &tmp, &quote, &i);
	while (str[++i])
	{
		if (quote == NONE)
		{
			if (!parse_char_unquote(&head, &tmp, str[i], &quote))
				return (NULL);
		}
		else if (!parse_char_quote(head, &tmp, str[i], &quote))
			return (NULL);
	}
	if (tmp)
		head = token_delimiter(&head, &tmp, str[i]);
	check_syntax(&head);
	maxishell->tokens = head;
	if (!parse_here_docs(maxishell, head))
		return (tkn_free(head), NULL);
	return (head);
}
