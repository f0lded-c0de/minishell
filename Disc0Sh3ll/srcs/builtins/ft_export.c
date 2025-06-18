#include "exec.h"

static int	print_invalid_identifier_error(char *var_name)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	free_sorted_env(char **sorted_env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(sorted_env[i]);
		i++;
	}
}

static char	**allocate_sorted_env(char **env, int size)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		sorted_env[i] = ft_strdup(env[i]);
		i++;
	}
	sorted_env[size] = NULL;
	return (sorted_env);
}

static void	sort_env_array(char **sorted_env, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(sorted_env[j], sorted_env[j + 1],
					ft_strlen(sorted_env[j])) > 0)
			{
				temp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**create_sorted_env(char **env, int *size)
{
	char	**sorted_env;

	*size = 0;
	while (env[*size])
		(*size)++;
	sorted_env = allocate_sorted_env(env, *size);
	sort_env_array(sorted_env, *size);
	return (sorted_env);
}

static void	print_env_entry(char *entry)
{
	int	j;

	ft_putstr_fd("declare -x ", 1);
	j = 0;
	while (entry[j] && entry[j] != '=')
		ft_putchar_fd(entry[j++], 1);
	if (entry[j] == '=')
	{
		ft_putstr_fd("=\"", 1);
		j++;
		ft_putstr_fd(entry + j, 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

static void	print_sorted_env(char **env)
{
	int		i;
	int		size;
	char	**sorted_env;

	sorted_env = create_sorted_env(env, &size);
	i = 0;
	while (i < size)
	{
		print_env_entry(sorted_env[i]);
		i++;
	}
	free_sorted_env(sorted_env, size);
	free(sorted_env);
}

static int	validate_var(char *var)
{
	char	*name;
	int		result;

	if (!ft_strchr(var, '='))
	{
		if (is_valid_varname(var))
			return (0);
		else
			return (print_invalid_identifier_error(var));
	}
	name = ft_substr(var, 0, ft_strchr(var, '=') - var);
	if (!is_valid_varname(name))
	{
		free(name);
		return (print_invalid_identifier_error(var));
	}
	free(name);
	return (0);
}

static int	update_existing_var(t_shell *shell, char *var, char *name)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_new_var(t_shell *shell, char *var, int env_size)
{
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!new_env)
		return (1);
	j = 0;
	while (j < env_size)
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[env_size] = ft_strdup(var);
	new_env[env_size + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	add_or_update_env(t_shell *shell, char *var)
{
	int		i;
	char	*name;
	int		result;

	if (!ft_strchr(var, '='))
		return (validate_var(var));
	name = ft_substr(var, 0, ft_strchr(var, '=') - var);
	if (!is_valid_varname(name))
	{
		free(name);
		return (print_invalid_identifier_error(var));
	}
	if (update_existing_var(shell, var, name))
	{
		free(name);
		return (0);
	}
	i = 0;
	while (shell->env[i])
		i++;
	result = add_new_var(shell, var, i);
	free(name);
	return (result);
}

int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	if (!args || !args[0])
	{
		print_sorted_env(shell->env);
		return (0);
	}
	status = 0;
	i = 0;
	while (args[i])
	{
		if (add_or_update_env(shell, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
