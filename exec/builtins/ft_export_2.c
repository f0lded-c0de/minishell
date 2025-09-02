#include "minishell.h"

static void	sort_env(char **env, int size)
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
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_env(char **env, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			ft_putchar_fd(env[i][j], 1);
			j++;
		}
		if (env[i][j] == '=')
		{
			ft_putstr_fd("=\"", 1);
			j++;
			ft_putstr_fd(env[i] + j, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	handle_env(char **env)
{
	int		size;
	int		i;
	char	**sorted_env;

	size = 0;
	i = 0;
	while (env[size])
		size++;
	sorted_env = malloc(sizeof(char *) * (size + 1));
	if (!sorted_env)
		return ;
	while (i < size)
	{
		sorted_env[i] = ft_strdup(env[i]);
		i++;
	}
	sorted_env[size] = NULL;
	sort_env(sorted_env, size);
	print_env(sorted_env, size);
	i = 0;
	while (i < size)
		free(sorted_env[i++]);
	free(sorted_env);
}
