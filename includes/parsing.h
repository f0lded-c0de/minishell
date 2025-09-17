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
char	*ft_expand(char *str);

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// Custom
# include "tokens.h"
# include "cmd_list.h"
# include "heredocs.h"

#endif
