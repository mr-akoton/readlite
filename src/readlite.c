/* ========================================================================== */
/*   File    : readlite.c                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 08:50:03 AM by mrakot00n                            */
/*   Updated : 2025/10/14 10:40:34 PM by mrakot00n                            */
/* ========================================================================== */

#include <readlite.h>
#include <rl_input.h>
#include <rl_term.h>
#include <rl_display.h>
#include <rl_util.h>
#include <rl_history.h>

char	*readlite(const char *prompt)
{
	char		input;
	t_line		line;
	t_history	history;

	if (rl_signal_setup() == -1)
		return (NULL);

	if (prompt == NULL)
		line.prompt = RL_DEFAULT_PROMPT;
	else
		line.prompt = prompt;
	
	// if (rl_history_load(RL_HISTORY_PATH, &history) == -1)
	// 	return (NULL);

	rl_enable_raw_mode();

	rl_display_prompt(line.prompt);
	rl_buffer_init(&line);
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

		rl_cursor_redisplay();
	}
	
	rl_cursor_move_down();
	// rl_history_save(RL_HISTORY_PATH, &history);
	
	rl_disable_raw_mode();
	return (line.content);
}
