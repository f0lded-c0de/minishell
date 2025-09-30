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

static void	init_maxishell(t_maxishell *maxishell, char **env)
{
	maxishell->exdata.env = split_cpy(env);
	maxishell->exdata.exit_status = 0;
	maxishell->exdata.pwd = 0;
	maxishell->exdata.oldpwd = 0;
	maxishell->pipeline = NULL;
	maxishell->exdata.exit_status = 0;
	maxishell->exdata.pid = NULL;
	update_pwd_env(&maxishell->exdata);
}

static int	is_input_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ' && (input[i] < '\t' || input[i] > '\v'))
			return (0);
	}
	return (1);
}

static void	handle_input(t_maxishell *maxishell, char *input)
{
	maxishell->tokens = tokeniser(maxishell, input);
	free(input);
	if (maxishell->tokens)
	{
		maxishell->pipeline = pipeline_builder(&maxishell->tokens, NULL);
		tkn_free(maxishell->tokens);
		if (maxishell->pipeline)
		{
			exit_handler(&maxishell->exdata);
			maxishell->exdata.exit_status
				= exec_pipeline(maxishell->pipeline, &maxishell->exdata);
			exec_free(maxishell->pipeline);
			if (maxishell->exdata.pid)
			{
				free(maxishell->exdata.pid);
				maxishell->exdata.pid = NULL;
			}
		}
	}
	else
		maxishell->exdata.exit_status = 1;
}

int	main(int ac, char **av, char **env)
{
	t_maxishell	maxishell;
	char		*input;

	(void)ac;
	(void)av;
	init_maxishell(&maxishell, env);
	while (1)
	{
		setup_signal();
		exit_handler(&maxishell.exdata);
		input = readline("Disc0Sh3ll$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (!is_input_empty(input))
			handle_input(&maxishell, input);
	}
	free_exdata(&maxishell.exdata);
	return (0);
}
