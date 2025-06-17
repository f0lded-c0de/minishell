#ifndef UTILS_H
# define UTILS_H

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// errors.c
void	puterr(char *error);
void	puterrno(char *error);

// str.c
char	*ft_strndup(const char *src, int n);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Errors
# define MLC_ERR "minishell: malloc failed"
# define QUO_ERR "minishell: bad syntax: unclosed quotes"
# define PAR_ERR "minishell: bad syntax: unclosed parenthesis"

#endif
