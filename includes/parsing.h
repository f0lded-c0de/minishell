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

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_quote {
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// expand.c
char	*ft_expand(t_exdata *exdata, char *str);

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// Custom
# include "tokens.h"
# include "pipeline.h"
# include "heredocs.h"

#endif
