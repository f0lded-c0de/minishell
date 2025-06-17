/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:02:12 by agenisse          #+#    #+#             */
/*   Updated: 2024/11/22 15:17:08 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned long	nbr;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int)n;
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd((char)(nbr % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((char)(nbr + '0'), fd);
}
