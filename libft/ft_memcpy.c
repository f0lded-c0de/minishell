/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:29:24 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/13 16:56:11 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n--)
		((char *)dest)[n] = ((char *)src)[n];
	return (dest);
}
/*
#include <stdio.h>
int main() 
{ 
	char src[] = "TEST"; 
	char dest[100]; 
	ft_memcpy(dest, src, ft_strlen(src)+1); 
	printf("dest string : %s", dest); 
	return 0; 
}*/
