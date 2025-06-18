#include "minishell"

char	*str_append_char(const char *src, const char c)
{
	char	*dst;
	size_t	len;
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
		dst[i] = str[i];
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
