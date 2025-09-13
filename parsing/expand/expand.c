#include "minishell.h"

char	*handle_unexpand(char *str, char *res, int i, int j)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * ((i - j) + 1));
	if (!tmp)
		return (puterr(MLC_ERR), NULL);

}

char	*expand_envar(char *str)
{
	char	*res;
	int		expand;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expand = 0;
	while (str[i])
	{
		if (expand == 0 && str[i] == '$')
		{
			expand = 1;
			
		}
	}
}
