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
	while (head)
	{
		printf("Type : [%s]     Token: [%s]\n", type_to_str(head->type), head->str);
		head = head->next;
	}
}

void run_token_test(const char *input)
{
	printf("Input : \"%s\"\n", input);
	t_tkn *tokens = tokeniser((char *)input);
	print_token_list(tokens);
	printf("----\n");
	tkn_free(tokens);
}
