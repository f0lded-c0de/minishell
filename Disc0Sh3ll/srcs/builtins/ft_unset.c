#include "exec.h"

static int is_valid_varname(char *name)
{
	int i;

	if (!name || !*name)
		return (0);
	if (!((name[0] >= 'a' && name[0] <= 'z') || 
		(name[0] >= 'A' && name[0] <= 'Z') || 
		name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || 
			(name[i] >= 'A' && name[i] <= 'Z') || 
			(name[i] >= '0' && name[i] <= '9') || 
			name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int print_invalid_name_error(char *var_name)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd(": invalid parameter name", 2);
	return (1);
}

static int unset_single_var(t_shell *shell, char *var_name)
{
	int i;
	int var_len;

	if (!is_valid_varname(var_name))
		return (print_invalid_name_error(var_name));
	var_len = ft_strlen(var_name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, var_len) == 0 && 
			shell->env[i][var_len] == '=')
		{
			free(shell->env[i]);
			while (shell->env[i])
			{
				shell->env[i] = shell->env[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int ft_unset(t_shell *shell, char **args)
{
	int i;
	int status;

	if (!shell || !args || !args[0])
		return (0);
	status = 0;
	i = 0;
	while (args[i])
	{
		if (unset_single_var(shell, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
