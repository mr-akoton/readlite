/* ========================================================================== */
/*   File    : readlite.c                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 08:50:03 AM by mrakot00n                            */
/*   Updated : 2025/10/13 12:04:35 PM by mrakot00n                            */
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

	if (rl_signal_setup() == -1)
		return (NULL);

	if (prompt == NULL)
		line.prompt = RL_DEFAULT_PROMPT;
	else
		line.prompt = prompt;
	
	rl_buffer_init(&line);
	rl_enable_raw_mode();
	rl_display_prompt(line.prompt);
	rl_term_size_update();

	while (1)
	{
		if (g_signal != 0)
		{
			if (rl_signal_handle(&line) == -1)
				break ;
		}

		if (read(STDIN_FILENO, &input, 1) == 1)
		{
			if (rl_input_handle(input, &line) == -1)
				break ;
		}
	}
	rl_cursor_move_down();

	rl_disable_raw_mode();
	return (line.content);
}
