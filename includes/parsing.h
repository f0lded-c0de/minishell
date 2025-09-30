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

#ifndef PARSING_H
# define PARSING_H

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */

// Custom
# include "tokens.h"
# include "pipeline.h"

typedef struct s_exdata		t_exdata;
/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum e_quote {
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

// struct
typedef struct s_expand_data {
	char	*res;
	int		expand;
	int		i[2];
}			t_expand_data;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// expand.c
char	*ft_expand(t_exdata *exdata, char *str);

// expand_utils.c
char	*handle_question(char *res, int exit_status);
char	*handle_expand(char **env, char *str, char *res, int i[2]);

#endif
