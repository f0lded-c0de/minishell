/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:08:23 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/12 21:32:47 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	octet;
	unsigned char	*ptr;

	octet = c;
	ptr = (unsigned char *)s;
	while (n--)
	{
		if (*ptr == octet)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
