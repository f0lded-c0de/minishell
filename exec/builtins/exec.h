#ifndef EXEC_H
# define EXEC_H

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// Custom
# include "../../../libft/libft.h"

// Defines
# define SHELL_NAME "Disc0Sh3ll"
# define INTERACTIVE_MODE 1
# define EXECUTION_MODE 0

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
	int		exit_status;
}	t_shell;

extern int	g_status;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// Builtins Shell Control
int		ft_echo(char **args);
int		ft_exit(int ac, char **args);

// Builtins Directory Navigation
int		ft_cd(t_shell *shell, int ac, char **args);
int		ft_pwd(void);

// Builtins Environment Management
int		t_env(char **env);
int		ft_unset(t_shell *shell, char **args);
int		ft_export(t_shell *shell, char **args);
void	handle_env(char **env);

// Builtins Utils
int		valid_varname(char *name);

// Signal Handling
void	handle_sigint(int sig);
void	setup_signal(int mode);
void	exit_handler(t_shell *shell);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */

#endif