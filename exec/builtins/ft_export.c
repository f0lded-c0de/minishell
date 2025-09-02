#include "minishell.h"

static int	print_error(char *var)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	update_env_2(t_shell *shell, char **new_var, char *var, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_var[j] = shell->env[j];
		j++;
	}
	new_var[i] = ft_strdup(var);
	if (!new_var[i])
	{
		free(new_var);
		return (1);
	}
	new_var[i + 1] = NULL;
	free(shell->env);
	shell->env = new_var;
	return (0);
}

static int	update_env(t_shell *shell, char *var, char *name)
{
	int		i;
	char	**new_var;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			if (!shell->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	new_var = malloc(sizeof(char *) * (i + 2));
	if (!new_var)
		return (1);
	update_env_2(shell, new_var, var, i);
	return (0);
}

static int	process_variable(t_shell *shell, char *var)
{
	char	*equals;
	char	*name;
	int		res;

	equals = ft_strchr(var, '=');
	if (!equals)
	{
		if (!valid_varname(var))
			return (print_error(var));
		return (0);
	}
	name = ft_substr(var, 0, (equals - var));
	if (!valid_varname(name))
	{
		free(name);
		return (print_error(var));
	}
	res = update_env(shell, var, name);
	free(name);
	return (res);
}

int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!args || !args[0])
	{
		handle_env(shell->env);
		return (0);
	}
	while (args[i])
	{
		if (process_variable(shell, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

int main(void)
{
    // Initialiser un environnement de test
    char *env_init[] = {
        "PATH=/usr/bin:/bin",
        "HOME=/home/user",
        "USER=student",
        NULL
    };
    
    // Créer la structure shell
    t_shell shell;
    
    // Allouer et copier l'environnement
    int env_size = 0;
    while (env_init[env_size])
        env_size++;
    
    shell.env = malloc(sizeof(char *) * (env_size + 1));
    if (!shell.env)
        return (1);
    
    for (int i = 0; i < env_size; i++)
        shell.env[i] = ft_strdup(env_init[i]);
    shell.env[env_size] = NULL;
    
    // Afficher l'environnement initial
    printf("=== Environnement initial ===\n");
    for (int i = 0; shell.env[i]; i++)
        printf("%s\n", shell.env[i]);
    
    // Test 1: export sans arguments
    printf("\n=== Test 1: export sans arguments ===\n");
    char *args1[] = {NULL};
    ft_export(&shell, args1);
    
    // Test 2: export avec un nom valide
    printf("\n=== Test 2: export FOO=bar ===\n");
    char *args2[] = {"FOO=bar", NULL};
    ft_export(&shell, args2);
    
    // Afficher l'environnement mis à jour
    printf("\n=== Environnement après Test 2 ===\n");
    for (int i = 0; shell.env[i]; i++)
        printf("%s\n", shell.env[i]);
    
    // Test 3: export avec un nom invalide
    printf("\n=== Test 3: export 123=invalid ===\n");
    char *args3[] = {"123=invalid", NULL};
    int status = ft_export(&shell, args3);
    printf("Statut de retour: %d\n", status);
    
    // Test 4: export avec plusieurs arguments
    printf("\n=== Test 4: export multiple ===\n");
    char *args4[] = {"A=1", "B=2", "C=3", NULL};
    ft_export(&shell, args4);
    
    // Afficher l'environnement final
    printf("\n=== Environnement final ===\n");
    for (int i = 0; shell.env[i]; i++)
        printf("%s\n", shell.env[i]);
    
    // Libérer la mémoire
    for (int i = 0; shell.env[i]; i++)
        free(shell.env[i]);
    free(shell.env);
    
    return (0);
}
