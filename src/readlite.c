/* ========================================================================== */
/*   File    : readlite.c                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 02:48:04 PM by mrakot00n                            */
/*   Updated : 2025/10/12 12:46:24 AM by mrakot00n                            */
/* ========================================================================== */

#include "rl_utils.h"
#include "rl_terminal.h"
#include "rl_input.h"

#include <readlite.h>

t_term	term;

char	*readlite(const char *prompt) {
	char 	input;
	t_line	line;

	init_line(&line);
	print_prompt(prompt);
	
	rl_enable_raw_mode();
	update_terminal_settings();
	
	while (read(STDIN_FILENO, &input, 1) != -1) {
		if (input == RL_EOL) {
			break ;
		}
		if (rl_handle_input(input, &line) == -1) {
			break ;
		}
	}
	rl_disable_raw_mode();
	return (line.content);
}
