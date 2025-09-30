/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkbomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:04:43 by bsamzun           #+#    #+#             */
/*   Updated: 2025/03/22 11:50:29 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
typedef struct	s_maxishell t_maxishell;
typedef struct	s_exdata	t_exdata;

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
# include <sys/stat.h>
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
void	puterrargno(char *error, char *arg);
void	puterrargerr(char *error1, char *arg, char *error2);

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
# define SH_ERR "disc0: "
# define MLC_ERR "disc0: malloc failed"
# define QUO_ERR "disc0: bad syntax: unclosed quotes"
# define PAR_ERR "disc0: bad syntax: unclosed parenthesis"
# define TKN_ERR "disc0: bad syntax: error near unexpected token "
# define HDC_WRN "disc0: warning: here_doc ended with end-of-file, expected "
# define PAT_ERR "disc0: command not found: "
# define DIR_ERR ": Is a directory"
# define PIP_ERR "disc0: pipe failed: "
# define FRK_ERR "disc0: fork failed: "
# define WPD_ERR "disc0: waitpid failed: "
# define DUP_ERR "disc0: dup failed: "
# define EXV_ERR "disc0: execve failed: "
# define ENV_ERR "disc0: where tf your env at bro???"
# define WTF_ERR "disc0: I have genuinely no clue what happened, sry bro"
# define CD_ARGS_ERR "disc0: cd: too many arguments"


#endif
