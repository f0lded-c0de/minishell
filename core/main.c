#include "minishell.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main(int ac, char **av, char **env)
{
	t_exdata	exdata;
	t_tkn		*tkn_lst;
	char		*input;
	/* int			status; */

	(void)ac;
	(void)av;
	exdata.env = env;
	exdata.exit_status = 0;
	update_pwd_env(&exdata);
	while (1)
	{
		setup_signal(INTERACTIVE_MODE);
		exit_handler(&exdata);
		input = readline("Disc0Sh3ll$ ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		tkn_lst = tokeniser(input);
		if (!tkn_lst)
			break;
		setup_signal(EXECUTION_MODE);
		exit_handler(&exdata);
		/* status = execute_cmd(char *cmd, char **envp) */
		free(input);
	}
	return (0);
}
