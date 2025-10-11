/* ========================================================================== */
/*   File    : terminal.c                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 03:00:04 PM by mrakot00n                            */
/*   Updated : 2025/10/11 11:13:56 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_terminal.h>
#include <rl_utils.h>

static struct termios	default_config;

/* ========================================================================== */
/*                                TERMINAL MODE                               */
/* ========================================================================== */

int rl_enable_raw_mode(void) {
	struct termios	raw_config;

	if (tcgetattr(STDIN_FILENO, &default_config) == -1) {
		perror("tcgetattr");
		return (-1);
	}

	raw_config = default_config;
	raw_config.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
							ICRNL | IXON);
	raw_config.c_oflag &= ~OPOST;
	raw_config.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	raw_config.c_cflag &= ~(CSIZE | PARENB);
	raw_config.c_cflag |= CS8;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_config) == -1) {
		perror("tcsetattr");
		return (-1);
	}
	return (0);
}

int rl_disable_raw_mode(void) {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_config) == -1) {
		perror("tcsetattr");
		return (-1);
	}
	return (0);
}


/* ========================================================================== */
/*                              TERMINAL SETTINGS                             */
/* ========================================================================== */

int	update_terminal_settings(void) {
	char			cursor_pos[11];
	struct winsize	ws;

	// Terminal size
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1) {
		perror("ioctl");
		return (-1);
	}
	term.width = ws.ws_col;
	term.height = ws.ws_row;

	// Cursor position
	term.cursor_x = 0;
	term.cursor_y = 0;
	
	putstr_fd(RL_REQUEST_CURSOR_POS, STDIN_FILENO);
	if (read_nullterm(STDIN_FILENO, cursor_pos, sizeof(cursor_pos)) == -1) {
		return (-1);
	}

	for (size_t i = 0; cursor_pos[i] && i < sizeof(cursor_pos); i++) {
		if (isdigit(cursor_pos[i])) {
			while (isdigit(cursor_pos[i])) {
				term.cursor_y = (term.cursor_y * 10) + (cursor_pos[i] - '0');
				i++;
			}
		} else if (cursor_pos[i] == ';') {
			i++;
			while (isdigit(cursor_pos[i])) {
				term.cursor_x = (term.cursor_x * 10) + (cursor_pos[i] - '0');
				i++;
			}
		}
	}

	return (0);
}