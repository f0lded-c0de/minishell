#ifndef UTILS_H
# define UTILS_H

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// errors.c
void	puterr(char *error);
void	puterrno(char *error);
void	puterrarg(char *error, char *arg);

// str.c
char	*str_append_char(char *src, char c);
char	str_last_c(char *str);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Errors
# define MLC_ERR "minishell: malloc failed"
# define QUO_ERR "minishell: bad syntax: unclosed quotes"
# define PAR_ERR "minishell: bad syntax: unclosed parenthesis"
# define TKN_ERR "minishell: bad syntax: error near unexpected token "

#endif
