#ifndef MINISHELL_H
# define MINISHELL_H
typedef struct	s_maxishell t_maxishell;

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Custom
# include "libft.h"
# include "parsing.h"
# include "exec.h"


/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */

typedef struct	s_maxishell {
	t_exdata	exdata;
	t_tkn		*tokens;
	t_exec		*pipeline;
}				t_maxishell;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// errors.c
void	puterr(char *error);
void	puterrno(char *error);
void	puterrarg(char *error, char *arg);

// str.c
char	*str_append_char(char *src, char c);
char	str_last_c(char *str);
void	free_split(char **split);
char	**split_cpy(char **src);
void	free_exdata(t_exdata *exdata);

// test.c
void	run_token_test(const char *input);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Errors
# define MLC_ERR "minishell: malloc failed"
# define QUO_ERR "minishell: bad syntax: unclosed quotes"
# define PAR_ERR "minishell: bad syntax: unclosed parenthesis"
# define TKN_ERR "minishell: bad syntax: error near unexpected token "
# define HDC_WRN "minishell: warning: here_doc ended with end-of-file, expected "
# define PAT_ERR "minishell: command not found: "
# define PIP_ERR "minishell: pipe failed: "
# define FRK_ERR "minishell: fork failed: "
# define WPD_ERR "minishell: waitpid failed: "
# define OPN_ERR "minishell: open failed: "
# define DUP_ERR "minishell: dup failed: "
# define EXV_ERR "minishell: execve failed: "
# define ENV_ERR "minishell: where tf your env at bro???"
# define WTF_ERR "minishell: I have genuinely no clue what happened, sry bro"


#endif
