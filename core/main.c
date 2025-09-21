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

void	print_here_doc(t_tkn *tkn)
{
	char	*buffer;
	int		read_count;

	printf("heredoc content :\n\n");
	buffer = malloc(sizeof(char) * 101);
	read_count = read(tkn->hd_fd, buffer, 100);
	if (read_count == -1)
	{
		puterrno("debug: read() failed lmao: ");
		free(buffer);
		return ;
	}
	buffer[read_count] = '\0';
	while (read_count > 0)
	{
		printf("%s\n\n", buffer);
		read_count = read(tkn->hd_fd, buffer, 100);
		if (read_count == -1)
		{
			puterrno("debug: read() failed lmao: ");
			free(buffer);
			return ;
		}
		buffer[read_count] = '\0';
	}
	free(buffer);
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
			print_here_doc(tmp);
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
	exdata.oldpwd = 0;
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
		if (!ft_strncmp(input, "exit", 4))
		{
			free(input);
			free_exdata(&exdata);
			return (0);
		}
		printf("Input : \"%s\"\n", input);
		tokens = tokeniser(env, input);
		setup_signal(EXECUTION_MODE);
		exit_handler(&exdata);
		/* status = execute_cmd(char *cmd, char **envp) */
		if (tokens)
			print_token_list(tokens);
		else
			printf("Tokenisation failed lol\n");
		free(input);
	}
	free_exdata(&exdata);
	return (0);
}
