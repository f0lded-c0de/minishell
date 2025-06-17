/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:02:01 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/13 14:46:15 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i]) && (s1[i] == s2[i]) && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	printf("%d \n", strncmp("test\200", "test\0", 6));
	printf("%d", ft_strncmp("test\200", "test\0", 6)); 
	return(0);
}*/
