/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:18:22 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/22 16:26:45 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_int(int n)
{
	int			i;
	long int	nb;

	nb = n;
	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				size;
	long int		nb;
	char			*new;

	nb = n;
	size = size_int(n);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size--] = '\0';
	if (nb == 0)
		new[0] = '0';
	if (nb < 0)
	{
		nb *= -1;
		new[0] = '-';
	}
	while (nb > 0)
	{
		new[size--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (new);
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	printf("LE RESULTAT : %s\n", ft_itoa(ft_atoi(av[1])));
}*/
