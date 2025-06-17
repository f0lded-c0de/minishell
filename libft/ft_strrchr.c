/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:52:06 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/19 15:57:06 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
				last = ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (last);
}
/*
#include <stdio.h>
int main()
{
    const char *str = "Bonjour, tout le monde!";
    char *result = ft_strrchr(str, 'o');

    if (result)
        printf(" : %ld\n", result - str);
    else
        printf("Caractère non trouvé.\n");

    return 0;
}
*/
