/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:24:58 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/19 10:38:21 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen((char *)s + start))
		len = ft_strlen((char *)s + start);
	new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < len)
	{
		new[i] = s[i + start];
		i++;
	}
	return (new);
}
