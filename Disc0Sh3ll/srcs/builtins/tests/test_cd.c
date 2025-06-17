#include "exec.h"
#include <stdio.h>

/**
 * Helper function to duplicate environment variables
 */
char **dup_env(char **env)
{
    int count = 0;
    char **new_env;
    
    // Count environment variables
    while (env[count])
        count++;
    
    // Allocate memory
    new_env = (char **)malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return (NULL);
    
    // Copy each variable
    count = 0;
    while (env[count])
    {
        new_env[count] = ft_strdup(env[count]);
        count++;
    }
    new_env[count] = NULL;
    
    return (new_env);
}

/**
 * Print current directory and relevant environment variables
 */
void print_state(t_shell *shell)
{
    char buffer[PATH_MAX];
    
    printf("\nCurrent directory: %s\n", getcwd(buffer, PATH_MAX));
    
    if (shell->tool->pwd)
        printf("PWD (internal): %s\n", shell->tool->pwd);
    else
        printf("PWD (internal): not set\n");
        
    if (shell->tool->oldpwd)
        printf("OLDPWD (internal): %s\n", shell->tool->oldpwd);
    else
        printf("OLDPWD (internal): not set\n");
    
    // Find PWD and OLDPWD in environment
    int i = 0;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
            printf("PWD (env): %s\n", shell->env[i]);
        else if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
            printf("OLDPWD (env): %s\n", shell->env[i]);
        i++;
    }
    printf("\n");
}

/**
 * Initialize shell structure
 */
t_shell *init_shell(char **env)
{
    t_shell *shell;
    
    shell = (t_shell *)malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    
    // Initialize tool structure
    shell->tool = (t_tool *)malloc(sizeof(t_tool));
    if (!shell->tool)
    {
        free(shell);
        return (NULL);
    }
    shell->tool->pwd = NULL;
    shell->tool->oldpwd = NULL;
    
    // Copy environment
    shell->env = dup_env(env);
    if (!shell->env)
    {
        free(shell->tool);
        free(shell);
        return (NULL);
    }
    
    return (shell);
}

/**
 * Clean up shell structure
 */
void cleanup_shell(t_shell *shell)
{
    int i = 0;
    
    if (shell->tool->pwd)
        free(shell->tool->pwd);
    if (shell->tool->oldpwd)
        free(shell->tool->oldpwd);
    free(shell->tool);
    
    while (shell->env[i])
    {
        free(shell->env[i]);
        i++;
    }
    free(shell->env);
    free(shell);
}

/**
 * Execute cd command with given arguments
 */
void test_cd(t_shell *shell, int ac, char **args)
{
    printf("======== Testing: ");
    for (int i = 0; i < ac; i++)
    {
        printf("%s ", args[i]);
    }
    printf("========\n");
    
    int result = ft_cd(shell, ac, args);
    printf("Return value: %d\n", result);
    print_state(shell);
}

int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
    char *test1[] = {"cd"};
    char *test2[] = {"cd", "/tmp"};
    char *test3[] = {"cd", "-"};
    char *test4[] = {"cd", ".."};
    char *test5[] = {"cd", "non_existent_dir"};
    
    (void)argc;
    (void)argv;
    
    // Initialize shell with environment
    shell = init_shell(envp);
    if (!shell)
    {
        printf("Failed to initialize shell\n");
        return (1);
    }
    
    // Initial state
    printf("======== Initial State ========\n");
    print_state(shell);
    
    // Test case 1: cd with no arguments (should go to HOME)
    test_cd(shell, 1, test1);
    
    // Test case 2: cd to specific directory
    test_cd(shell, 2, test2);
    
    // Test case 3: cd - (go to previous directory)
    test_cd(shell, 2, test3);
    
    // Test case 4: cd .. (go up one directory)
    test_cd(shell, 2, test4);
    
    // Test case 5: cd to non-existent directory (should fail)
    test_cd(shell, 2, test5);
    
    // Clean up
    cleanup_shell(shell);
    
    return (0);
}