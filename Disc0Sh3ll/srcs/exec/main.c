#include "../builtins/exec.h"

int	main_shell_loop(t_shell *shell)
{
	char	*input;
	int		status;

	while (1)
	{
		setup_signal(INTERACTIVE_MODE);
		exit_handler(shell);
		input = readline("Disc0Sh3ll$ ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		parsing;
		setup_signal(EXECUTION_MODE);
		exit_handler(shell);
		status = execute_cmd(char *cmd, char **envp)
		free(input);
	}
	return (0);
}