#ifndef UTILS_H
# define UTILS_H

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// errors.c
void	puterr(char *error);
void	puterrno(char *error);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Errors
# define Q_ERR "minishell: bad syntax: unclosed quotes"

#endif
