#include "minishell.h"

static void	frexit(t_exec *pipeline, t_exdata *exdata, char *error)
{
	if (error)
		puterrarg(error, pipeline->args[0]);
	exec_free(pipeline);
	free_exdata(exdata);
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_exec *pipeline, t_exdata *exdata)
{
	char	**args;
	char	**env;
	char	*path;

	if (!pipeline->args)
		frexit(pipeline, exdata, NULL);
	path = get_cmd_path(pipeline->args[0], exdata->env);
	if (!path)
		frexit(pipeline, exdata, PAT_ERR);
	args = pipeline->args;
	env = exdata->env;
	pipeline->args = NULL;
	exdata->env = NULL;
	free_exdata(exdata);
	exec_free(pipeline);
	execve(path, args, env);
	free_split(args);
	free_split(env);
	free(path);
	puterrno(EXV_ERR);
	exit(EXIT_FAILURE);
}
