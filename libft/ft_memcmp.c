/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:21:48 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/12 20:34:40 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*pts1;
	unsigned char	*pts2;

	pts1 = (unsigned char *)s1;
	pts2 = (unsigned char *)s2;
	while (n--)
	{
		if (*pts1 != *pts2)
			return (*pts1 - *pts2);
		pts1++;
		pts2++;
	}
	return (0);
}
/*
#include <stdio.h>

int main()
{
    char str1[] = "Hello, world!";
    char str2[] = "Hello, world!";
    char str3[] = "Hello, everyone!";

    int result = ft_memcmp(str1, str2, 13);  // Comparer les 13 premiers octets
    if (result == 0)
        printf("Les deux chaînes sont égales.\n");
    else
        printf("Les deux chaînes sont différentes.\n");

    result = ft_memcmp(str1, str3, 13);  // Comparer les 13 premiers octets
    if (result == 0)
        printf("Les deux chaînes sont égales.\n");
    else
        printf("Les deux chaînes sont différentes.\n");

    return 0;
}
*/
