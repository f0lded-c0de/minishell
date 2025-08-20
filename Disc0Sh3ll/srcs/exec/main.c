#include "../builtins/exec.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main_shell_loop(t_shell *shell)
{
	char	*input;
	int		status;

	while (1)
	{
		setup_signals(INTERACTIVE_MODE);
		input = readline("Disc0Sh3ll$ ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		parsing

		setup_signals(EXECUTION_MODE);
		status = execute_cmd(char *cmd, char **envp)
		free(input);
	}
	return (0);
}