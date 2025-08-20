#include "../builtins/exec.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal(int mode)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (mode == INTERACTIVE_MODE)
		sa_quit.sa_handler = SIG_IGN;
	else if (mode == EXECUTION_MODE)
	{
		sa_int.sa_handler = SIG_DFL;
		sa_quit.sa_handler = SIG_DFL;
	}
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
