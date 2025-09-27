#include "minishell.h"

void	print_pipeline(t_exec *pipeline)
{
	t_exec	*tmp;

	if (!pipeline)
	{
		printf("Empty pipeline\n");
		return ;
	}

}

int	is_input_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (c == ' ' && (c < '\t' || c > '\v'))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_maxishell	maxishell;
	char		*input;
	/* int			status; */

	(void)ac;
	(void)av;
	maxishell.exdata.env = split_cpy(env);
	maxishell.exdata.exit_status = 0;
	maxishell.exdata.pwd = 0;
	maxishell.exdata.oldpwd = 0;
	maxishell.pipeline = NULL;
	update_pwd_env(&maxishell.exdata);
	while (1)
	{
		setup_signal(INTERACTIVE_MODE);
		exit_handler(&maxishell.exdata);
		input = readline("Disc0Sh3ll$ ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		if (!is_input_empty(input))
		{
			// to remove [
			if (!ft_strncmp(input, "exit", 4))
			{
				free(input);
				free_exdata(&maxishell.exdata);
				return (0);
			}
			printf("Input : \"%s\"\n", input);
			// ] to remove
			maxishell.tokens = tokeniser(&maxishell, input);
			free(input);
			if (!maxishell.tokens)
				break;
			maxishell.pipeline = pipeline_builder(&maxishell.tokens);
			if (!maxishell.pipeline)
				break;
			setup_signal(EXECUTION_MODE);
			exit_handler(&maxishell.exdata);
			status = execute_cmd(char *cmd, char **envp)
		}
	}
	free_exdata(&maxishell.exdata);
	return (0);
}
