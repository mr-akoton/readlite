/* ========================================================================== */
/*   File    : term.c                                                         */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:55:25 PM by mrakot00n                            */
/*   Updated : 2025/10/12 10:27:53 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_term.h>

t_term	g_tconf;

int	rl_term_config_update(void)
{
	struct winsize ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		perror("rl_term_config_update: ioctl");
		return (-1);
	}
	g_tconf.width = ws.ws_col;
	g_tconf.height = ws.ws_row;
	
	return (0);
}
