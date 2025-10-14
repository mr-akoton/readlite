/* ========================================================================== */
/*   File    : terminal.c                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/14 09:49:49 PM by mrakot00n                            */
/*   Updated : 2025/10/14 09:49:50 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_term.h>

t_term					g_tconf;
static struct termios	default_config;

/* ========================================================================== */
/*                                  SETTINGS                                  */
/* ========================================================================== */

int	rl_term_size_update(void)
{
	struct winsize ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		perror("rl_term_size_update: ioctl");
		return (-1);
	}
	g_tconf.width = ws.ws_col;
	g_tconf.height = ws.ws_row;
	return (0);
}

/* ========================================================================== */
/*                                  RAW MODE                                  */
/* ========================================================================== */

int	rl_enable_raw_mode(void)
{
	struct termios	raw_config;

	if (tcgetattr(STDIN_FILENO, &default_config) == -1)
	{
		perror("rl_enable_raw_mode: tcgetattr");
		return (-1);
	}

	// NOTE: This configuration can be found in the manual of termios
	//       cfmakeraw() works the same but I wanted to have full control and
	//       undestanding on the settings.
	//       ISIG was removed due to signal handling.
	
	raw_config = default_config;
	raw_config.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
							ICRNL | IXON);
	raw_config.c_oflag &= ~OPOST;
	raw_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	raw_config.c_cflag &= ~(CSIZE | PARENB);
	raw_config.c_cflag |= CS8;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_config) == -1)
	{
		perror("rl_enable_raw_mode: tcsetattr");
		return (-1);
	}
	return (0);
}

int	rl_disable_raw_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_config) == -1)
	{
		perror("rl_disable_raw_mode: tcsetattr");
		return (-1);
	}
	return (0);
}
