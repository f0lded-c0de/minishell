#include "minishell.h"

void	puterr(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	puterrno(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	puterrarg(char *error, char *arg)
{
	write(2, error, ft_strlen(error));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}
