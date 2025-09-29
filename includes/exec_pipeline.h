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


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// exec_pipeline.c
int		exec_pipeline(t_exec *pipeline, t_exdata *exdata);

// utils.c
t_bltn	is_bltn(char *str);
int		get_cmd_count(t_exec *pipeline);

// redirs.c
int		handle_redirs(t_exec *pipeline);

// path.c
char	*get_cmd_path(char *cmd, char **envp);

// exec_bltn.c
int		forkless_bltn(t_exec *pipeline, t_exdata *exdata);
int		exec_bltn(t_exec *pipeline, t_exdata *exdata);
int		get_ac(char **av);

// exec_cmd.c
void	exec_cmd(t_exec *pipeline, t_exdata *exdata);

// quote.c
char	**unquote(char **env, char **args);

#endif
