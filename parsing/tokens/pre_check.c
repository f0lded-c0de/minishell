#include "minishell.h"

void	null_init_ints_counters(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int	check_unclosed(char *str)
{
	int	single_count;
	int	double_count;
	int	par_count;
	int	i;

	null_init_ints_counters(&single_count, &double_count, &par_count, &i);
	while (str[i])
	{
		if (str[i] == '\'' && !(double_count % 2))
			single_count++;
		if (str[i] == '"' && !(single_count % 2))
			double_count++;
		if (str[i] == '(' && !(double_count % 2) && !(single_count % 2))
			par_count++;
		if (str[i] == ')' && !(double_count % 2) && !(single_count % 2))
			par_count--;
		i++;
	}
	if ((single_count % 2) || (double_count % 2))
		return (puterr(QUO_ERR), 0);
	if (par_count != 0)
		return (puterr(PAR_ERR), 0);
	return (1);
}
