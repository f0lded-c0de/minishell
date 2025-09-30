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

#ifndef CMD_LIST_H
# define CMD_LIST_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// struct
typedef struct	s_exec {
	char			**args;
	struct s_exec	*next;
	struct s_exec	*prev;
	t_tkn			*redin;
	t_tkn			*redout;
}					t_exec;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// pipeline.c
t_exec	*pipeline_builder(t_tkn **tkn_head, t_exec *prev);

// utils.c
t_exec	*exec_new(void);
void	exec_free(t_exec *cmd);
t_tkn	*get_next_pipe(t_tkn *head);

#endif
