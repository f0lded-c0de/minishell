#include "minishell.h"

const char *type_to_str(t_tkn_type type)
{
	static const char *names[] = {
		"WORD", "PIPE", "OR", "AND",
		"RED_IN", "RED_OUT", "HEREDOC", "APP_OUT",
		"PAR_OPEN", "PAR_CLOSE"
	};

	if (type >= 0 && type <= PAR_CLOSE)
		return names[type];
	else
		return "UNKNOWN";
}

void print_token_list(t_tkn *head)
{
	t_tkn	*tmp;
	if (!head)
	{
		printf("Empty token list");
		return;
	}
	tmp = head;
	while (tmp)
	{
		printf("Type : [%s]     Token: [%s]\n", type_to_str(tmp->type), tmp->str);
		if (tmp->type == HEREDOC)
			printf("hd_fd : %d", tmp->hd_fd);
		tmp = tmp->next;
	}
	printf("----\n");
	tkn_free(head);
}

int	main(int ac, char **av, char **env)
{
	t_exdata	exdata;
	t_tkn		*tokens;
	char		*input;
	/* int			status; */

	(void)ac;
	(void)av;
	exdata.env = split_cpy(env);
	exdata.exit_status = 0;
	exdata.pwd = 0;
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
		printf("Input : \"%s\"\n", input);
		tokens = tokeniser(input);
		setup_signal(EXECUTION_MODE);
		exit_handler(&exdata);
		/* status = execute_cmd(char *cmd, char **envp) */
		if (tokens)
			print_token_list(tokens);
		free(input);
	}
	return (0);
}
