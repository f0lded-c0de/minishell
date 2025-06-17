/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:29:26 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/12 21:43:20 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	size_t	len;

	len = ft_strlen((char *)src);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, (char *)src, len + 1);
	return ((char *)new);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	printf("%s", ft_strdup(argv[1]));
}*/
