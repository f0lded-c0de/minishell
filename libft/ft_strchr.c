/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:43:57 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/19 15:56:26 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>
int main()
{
    const char *str = "Bonjour, tout le monde!";
    char *result = ft_strchr(str, 'z');

    if (result)
        printf("Le caractère 't' trouvé à la position : %ld\n", result - str);
    else
        printf("Caractère non trouvé.\n");

    return 0;
}
*/
