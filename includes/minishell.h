#ifndef MINISHELL_H
# define MINISHELL_H

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <climits>
# include <cstdlib>

// Custom
# include "libft.h"
# include "parsing.h"
# include "tokens.h"
# include "utils.h"


/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// errors.c
void	puterr(char *error);
void	puterrno(char *error);
void	puterrarg(char *error, char *arg);

// str.c
char	*str_append_char(char *src, char c);
char	str_last_c(char *str);

// test.c
void	run_token_test(const char *input);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Errors
# define MLC_ERR "minishell: malloc failed"
# define QUO_ERR "minishell: bad syntax: unclosed quotes"
# define PAR_ERR "minishell: bad syntax: unclosed parenthesis"
# define TKN_ERR "minishell: bad syntax: error near unexpected token "


#endif
