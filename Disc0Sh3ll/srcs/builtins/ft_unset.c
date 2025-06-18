#include "exec.h"

static int	print_invalid_name_error(char *var_name)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd(": invalid parameter name", 2);
	return (1);
}

static int	unset_single_var(t_shell *shell, char *var_name)
{
	int	i;
	int	var_len;

	if (!is_valid_varname(var_name))
		return (print_invalid_name_error(var_name));
	var_len = ft_strlen(var_name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, var_len) == 0
			&& shell->env[i][var_len] == '=')
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

int	ft_unset(t_shell *shell, char **args)
{
	int	i;
	int	status;

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
