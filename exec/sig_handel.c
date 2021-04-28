# include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	con.exit_stat = 130;
}


void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit: 3", 1);
	con.exit_stat = 131;
}