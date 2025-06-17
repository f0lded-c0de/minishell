/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:05:28 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/12 21:12:54 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	dest;

	i = 0;
	n = 1;
	dest = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
				n = n * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		dest = ((dest * 10) + (str[i] - '0'));
		i++;
	}
	return (dest * n);
}
/*
#include <stdlib.h>
#include <stdio.h>
int main (int argc,char ** argv)
{
	if (argc == 2)
	{
		printf("%d\n", ft_atoi(argv[1]));
		printf("%d", atoi(argv[1]));
	}
	if (argc != 2)
		return (0);
}
*/
