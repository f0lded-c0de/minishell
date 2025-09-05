#include "minishell.h"

static void	handle_here_doc(t_tkn *hd)
{
	char	**delim;
	int		expand;

	delim = ft_split(hd->next->str, '"')
	expand =;

}

void	parse_here_docs(t_tkn *head)
{
	while (head)
	{
		if (head->type == HEREDOC && head->next)
	}
}
