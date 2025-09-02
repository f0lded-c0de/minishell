#include "exec.h"

static int	update_oldpwd(t_shell *shell)
{
	int	i;

	if (!shell->tool->pwd)
		return (0);
	if (shell->tool->oldpwd)
		free(shell->tool->oldpwd);
	shell->tool->oldpwd = shell->tool->pwd;
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->env[i])
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin("OLDPWD=", shell->tool->oldpwd);
	}
	return (0);
}

static int	update_pwd(t_shell *shell, char *cwd)
{
	int	i;

	shell->tool->pwd = ft_strdup(cwd);
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], "PWD=", 4) != 0)
		i++;
	if (shell->env[i])
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin("PWD=", shell->tool->pwd);
	}
	return (0);
}

static int	update_pwd_env(t_shell *shell)
{
	char	buffer[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buffer, PATH_MAX);
	if (!cwd)
		return (1);
	update_oldpwd(shell);
	update_pwd(shell, cwd);
	return (0);
}

static char	*get_home_dir(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_target_dir(t_shell *shell, int ac, char **args)
{
	char	*home;

	if (ac == 1)
	{
		home = get_home_dir(shell->env);
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	else if (ac == 2 && ft_strncmp(args[1], "-", 1) == 0)
	{
		if (!shell->tool->oldpwd)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putendl_fd(shell->tool->oldpwd, 1);
		return (shell->tool->oldpwd);
	}
	return (args[1]);
}

int	ft_cd(t_shell *shell, int ac, char **args)
{
	char	*target_dir;

	target_dir = get_target_dir(shell, ac, args);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (update_pwd_env(shell));
}
