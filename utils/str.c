#include "minishell"

char	*ft_strndup(const char *src, int n)
{
	char	*new;
	size_t	len;

	len = ft_strlen((char *)src);
	if (len > n)
		len = n;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (puterr(MLC_ERR), NULL);
	ft_strlcpy(new, (char *)src, len + 1);
	return ((char *)new);
}
