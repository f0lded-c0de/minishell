/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkbomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:04:43 by bsamzun           #+#    #+#             */
/*   Updated: 2025/03/22 11:50:29 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	puterr(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	puterrno(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	puterrarg(char *error, char *arg)
{
	write(2, error, ft_strlen(error));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	puterrargno(char *error, char *arg)
{
	write(2, error, ft_strlen(error));
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	puterrargerr(char *error1, char *arg, char *error2)
{
	write(2, error1, ft_strlen(error1));
	write(2, arg, ft_strlen(arg));
	write(2, error2, ft_strlen(error2));
	write(2, "\n", 1);
}
