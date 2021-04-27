# include "../minishell.h"

void	sigin_handl(int sig)
{
	ft_putendl_fd("", 1);
	con.exit_stat = 130;
}