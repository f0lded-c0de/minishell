/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:35:09 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/22 17:52:37 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_copy(const char *s, int start, int end)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = end - start;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (start < end)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	i = 0;
	j = 0;
	index = -1;
	split = ft_calloc(sizeof(char *), (ft_count_word(s, c) + 1));
	if (!s || !split)
		return (NULL);
	while ((size_t)i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || (size_t)i == ft_strlen((char *)s)) && index >= 0)
		{
			split[j] = ft_copy(s, index, i);
			if (!split[j++])
				return (free_split(split), NULL);
			index = -1;
		}
		i++;
	}
	return (split);
}
/*#include <stdio.h>
int	main(int ac, char **av)
{
	int	i = 0;
	while (i < ac)
	{
		printf("%s\n", ft_split(av[1], av[2][0])[i]);
		i++;
	}
}
*/ 