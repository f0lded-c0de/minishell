#include "minishell.h"

static char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*check_path(char **paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*path;

	if (!cmd || !*cmd)
		return (NULL);
	path_env = find_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	path = check_path(paths, cmd);
	free_split(paths);
	if (!path && (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')))
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
	return (path);
}
