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

#ifndef HEREDOCS_H
# define HEREDOCS_H

typedef struct s_maxishell	t_maxishell;
/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// struct
typedef struct	s_delim_status {
	int				index;
	int				start_word;
	t_quote			quote;
}					t_delim_status;

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// heredocs.c
int		parse_here_docs(t_maxishell *maxishell, t_tkn *head);

// get_delim.c
char	*get_delim(char *str);

// utils.c
int		ft_strcmp(char *s1, char *s2);
void	close_pipes(int pipe[2]);
void	finish_hd(t_maxishell *maxishell, char *input, char *delim, int fd);
void	hd_parent_setup_signal(struct sigaction *old_int);
void	hd_child_setup_signal(void);


/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */

#endif
