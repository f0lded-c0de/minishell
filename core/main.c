#include "minishell.h"

const char *type_to_str(t_tkn_type type)
{
	static const char *names[] = {
		"WORD", "PIPE", "RED_IN", "RED_OUT", "HEREDOC", "APP_OUT"
	};

	if (type >= 0 && type <= APP_OUT)
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
	tkn_free(head);
}

void	print_pipeline(t_exec *pipeline)
{
	t_exec	*tmp;
	int		i;
	int		j;

	if (!pipeline)
	{
		printf("Empty pipeline\n");
		return ;
	}
	tmp = pipeline;
	i = 1;
	while (tmp)
	{
		printf("NODE %d :\n\n", i);
		if (tmp->args)
		{
			j = -1;
			printf("Args :\n");
			while (tmp->args[++j])
				printf("	%s\n", tmp->args[j]);
			printf("\n");
		}
		if (tmp->redin)
		{
			printf("Redin :\n");
			print_token_list(tmp->redin);
			tmp->redin = NULL;
			printf("\n");
		}
		if (tmp->redout)
		{
			printf("Redout :\n");
			print_token_list(tmp->redout);
			tmp->redout = NULL;
			printf("\n");
		}
		printf("\n-----\n\n");
		tmp = tmp->next;
		i++;
	}
}

int	is_input_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ' && (input[i] < '\t' || input[i] > '\v'))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_maxishell	maxishell;
	char		*input;

	(void)ac;
	(void)av;
	maxishell.exdata.env = split_cpy(env);
	maxishell.exdata.exit_status = 0;
	maxishell.exdata.pwd = 0;
	maxishell.exdata.oldpwd = 0;
	maxishell.pipeline = NULL;
	maxishell.exdata.exit_status = 0;
	maxishell.exdata.pid = NULL;
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
			maxishell.tokens = tokeniser(&maxishell, input);
			free(input);
			if (maxishell.tokens)
			{
				maxishell.pipeline = pipeline_builder(&maxishell.tokens, NULL);
				tkn_free(maxishell.tokens);
				if (maxishell.pipeline)
				{
					setup_signal(EXECUTION_MODE);
					exit_handler(&maxishell.exdata);
					maxishell.exdata.exit_status
						= exec_pipeline(maxishell.pipeline, &maxishell.exdata);
					exec_free(maxishell.pipeline);
					if (maxishell.exdata.pid)
						free(maxishell.exdata.pid);
				}
			}
		}
	}
	free_exdata(&maxishell.exdata);
	return (0);
}
