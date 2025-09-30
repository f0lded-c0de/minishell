#ifndef EXEC_H
# define EXEC_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */

typedef struct s_exdata
{
	char	*pwd;
	char	*oldpwd;
	char	**env;
	int		exit_status;
	int		*pid;
}	t_exdata;

extern int	g_status;

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
# include <sys/stat.h>
# include <fcntl.h>

// Custom
# include "exec_pipeline.h"

// Defines
# define SHELL_NAME "Disc0Sh3ll"
# define INTERACTIVE_MODE 1
# define EXECUTION_MODE 0

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// Builtins Shell Control
int					ft_echo(char **args);
int					ft_exit(int ac, char **args, t_exec *ppline, t_exdata *dt);

// Builtins Directory Navigation
int					ft_cd(t_exdata *shell, int ac, char **args);
int					ft_pwd(void);
int					update_pwd_env(t_exdata *shell);

// Builtins Environment Management
int					ft_env(char **env);
int					ft_unset(t_exdata *shell, char **args);
int					ft_export(t_exdata *shell, char **args);
void				handle_env(char **env);

// Builtins Utils
int					valid_varname(char *name);
unsigned long long	ft_atoull(const char *str);

// Signal Handling
void				handle_sigint(int sig);
void				setup_signal(void);
void				exit_handler(t_exdata *shell);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */

#endif
