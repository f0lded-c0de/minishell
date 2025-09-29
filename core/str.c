#include "minishell.h"

char	*str_append_char(char *src, char c)
{
	char	*dst;
	int	len;
	int		i;

	len = 0;
	if (src)
		len = ft_strlen((char *)src);
	dst = malloc(sizeof(char) * (len + 2));
	if (dst == NULL)
	{
		if (src)
			free(src);
		return (puterr(MLC_ERR), NULL);
	}
	i = -1;
	while (++i < len)
		dst[i] = src[i];
	dst[i++] = c;
	dst[i] = '\0';
	if (src)
		free(src);
	return ((char *)dst);
}

char	str_last_c(char *str)
{
	int	i;

	if (!str || !str[0])
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (str[i - 1]);
}

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
	}
}

char	**split_cpy(char **src)
{
	char	**dst;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = NULL;
	while (--i >= 0)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (free_split(dst), NULL);
	}
	return (dst);
}

void	free_exdata(t_exdata *exdata)
{
	free_split(exdata->env);
	if (exdata->pwd)
		free(exdata->pwd);
	if (exdata->oldpwd)
		free(exdata->oldpwd);
	if (exdata->pid)
		free(exdata->pid);
}
