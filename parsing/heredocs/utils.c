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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	close_pipes(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	hd_child_setup_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = SIG_DFL;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	hd_parent_setup_signal(struct sigaction *old_int)
{
	struct sigaction	ign;

	ft_memset(old_int, 0, sizeof(*old_int));
	ft_memset(&ign, 0, sizeof(ign));
	ign.sa_handler = SIG_IGN;
	ign.sa_flags = 0;
	sigaction(SIGINT, &ign, old_int);
}

void	finish_hd(t_maxishell *maxishell, char *input, char *delim, int fd)
{
	if (input)
		free(input);
	else
		puterrarg(HDC_WRN, delim);
	free(delim);
	close(fd);
	free_split(maxishell->exdata.env);
}
