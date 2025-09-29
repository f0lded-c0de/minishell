#include "minishell.h"

int	g_status = 0;

void	handle_sigint(int sig)
{
	g_status = sig;

	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exit_handler(t_exdata *shell)
{
	if (g_status == SIGINT)
		shell->exit_status = 130;
	if (g_status == SIGQUIT)
		shell->exit_status = 131;
}

void	setup_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
