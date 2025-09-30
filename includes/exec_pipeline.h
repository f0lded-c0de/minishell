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

#ifndef EXEC_PIPELINE_H
# define EXEC_PIPELINE_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// struct
typedef enum	e_bltn {
	NOT_BLTN,
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
}					t_bltn;

typedef struct	s_quote_data {
	char	**res;
	char	**tmps;
	char	*tmp;
	int		i;
	t_quote	quote;
}			t_quote_data;

typedef struct	s_redir_data {
	char	*res;
	char	*tmp;
	int		i;
	t_quote	quote;
}			t_redir_data;

typedef struct s_path_data {
	char		*path_env;
	char		**paths;
	char		*path;
	struct stat	st;
}				t_path_data;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// exec_pipeline.c
int		exec_pipeline(t_exec *pipeline, t_exdata *exdata);

// pipeline_utils.c
int		pipe_and_sig(t_exec *pipeline, int pipe_fd[2]);
int		fork_and_check(t_exdata *exdata, int i);
int		pipe_and_fork(t_exec *ppl, t_exdata *exdata, int p_fd[2], int i);
void	up_fd_and_go_on(t_exec **pipeline, int p_fd[2], int *fd_in, int *i);
int		wait_and_get_stat(t_exdata *exdata, int	*status, int cmd_count);

// pipeline_utils2.c
int		brexit(t_exec *pipeline, t_exdata *exdata, int i);
void	child_signal(int sig);
void	child_setup_signal(void);
void	handle_child(t_exec *pipeline, t_exdata *exdata, int pipe[2], int fd_in);

// utils.c
t_bltn	is_bltn(char *str);
int		get_cmd_count(t_exec *pipeline);

// split_merge.c
char	**split_merge(char **src, char **add);

// redirs.c
int		handle_redirs(t_exec *pipeline, t_exdata *exdata);

// redirs_utils.c
char	*str_append_str_redir(char *s1, char *s2);
void	null_init_redir(int *i, t_quote *quote, char **res, char **tmp);
int		expappend(t_exdata *exdata, char **tmp, char **res, int	mode);
int		handle_when_quote(t_redir_data *dt, t_exdata *exdata, char *str);

// path.c
char	*get_cmd_path(char *cmd, char **envp);

// path_utils.c
int		get_start(char *cmd);
char	*get_mid(char *cmd, t_path_data *dt);
void	get_end(void);

// exec_bltn.c
int		forkless_bltn(t_exec *pipeline, t_exdata *exdata);
int		exec_bltn(t_exec *pipeline, t_exdata *exdata);
int		get_ac(char **av);

// exec_cmd.c
void	exec_cmd(t_exec *pipeline, t_exdata *exdata);

// quote.c
char	**unquote(t_exdata *exdata, char **args);

// quote_utils.c
int		split_n_merge(char **tmp, char ***res, char ***tmps, t_quote mode);
void	update_quote(char *str, t_quote *quote, int i);
void	handle_end(t_exdata *exdata, char ***res, char **tmp);
int		str_append_char_bis(char **res, char **tmp, char *str, int i);
void	null_init_quote(int *i, t_quote *quote, char ***res, char **tmp);

#endif
