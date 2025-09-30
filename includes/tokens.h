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

#ifndef TOKENS_H
# define TOKENS_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_tkn_type {
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APP_OUT,
}	t_tkn_type;

// struct
typedef struct	s_tkn {
	char			*str;
	t_tkn_type		type;
	int				hd_fd;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}					t_tkn;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// tokenisation.c
t_tkn	*tokeniser(t_maxishell *maxishell, char *str);

// utils.c
t_tkn	*tkn_new(char *str);
void	tkn_append(t_tkn **start, t_tkn *new);
void	tkn_rm(t_tkn *tkn);
void	tkn_rm_next(t_tkn *tkn);
void	tkn_free(t_tkn *tokens);

// check.c
int		check_unclosed(char *str);
void	check_syntax(t_tkn **head);
void	check_par(t_tkn **head);

// is_charset.c
int		is_operator(char c);
int		is_double_operator(char c);
int		is_space(char c);

#endif
