/* ========================================================================== */
/*   File    : term_mode.c                                                    */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:19:51 AM by mrakot00n                            */
/*   Updated : 2025/10/12 10:26:52 AM by mrakot00n                            */
/* ========================================================================== */

#include <rl_term.h>

static struct termios	default_config;

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
	
	raw_config = default_config;
	raw_config.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
							ICRNL | IXON);
	raw_config.c_oflag &= ~OPOST;
	raw_config.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
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
