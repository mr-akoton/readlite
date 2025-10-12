/* ========================================================================== */
/*   File    : readlite.c                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 08:50:03 AM by mrakot00n                            */
/*   Updated : 2025/10/12 12:29:46 PM by mrakot00n                            */
/* ========================================================================== */

#include <readlite.h>
#include <rl_input.h>
#include <rl_term.h>
#include <rl_display.h>
#include <rl_util.h>

char	*readlite(const char *prompt)
{
	char	input;
	t_line	line;

	rl_buffer_init(&line);
	rl_display_prompt(prompt);
	rl_enable_raw_mode();

	while (read(STDIN_FILENO, &input, 1) != -1)
	{
		if (rl_handle_input(input, &line) == -1)
			break ;
	}
	putstr_in(RL_MOVE_CURSOR_NLINE);

	rl_disable_raw_mode();
	return (line.content);
}