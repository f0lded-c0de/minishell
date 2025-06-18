#ifndef EXEC_H
# define EXEC_H

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

// Custom
# include "../../../libft/libft.h"

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */

typedef struct s_tool
{
	char	*pwd;
	char	*oldpwd;
}	t_tool;

typedef struct s_shell
{
	t_tool	*tool;
	char	**env;
}	t_shell;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// Builtins Shell Control
int	ft_echo(char **args);
int	ft_exit(int ac, char **args);

// Builtins Directory Navigation
int	ft_cd(t_shell *shell, int ac, char **args);
int	ft_pwd(void);

// Builtins Environment Management
int	ft_env(char **env);
int	ft_unset(t_shell *shell, char **args);

// Builtins Utils
int	is_valid_varname(char *name);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */

#endif