/* ========================================================================== */
/*   File    : render.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:28:55 AM by mrakot00n                            */
/*   Updated : 2025/10/12 08:39:47 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_display.h>
#include <rl_util.h>

/* ========================================================================== */
/*                               PROMPT DISPLAY                               */
/* ========================================================================== */

void	rl_display_prompt(const char *prompt)
{
	if (prompt == NULL)
		putstr_in(RL_DEFAULT_PROMPT);
	else
		putstr_in(prompt);
}

/* ========================================================================== */
/*                               BUFFER DISPLAY                               */
/* ========================================================================== */

void	rl_display_buffer(t_line *line)
{
	putstr_in(RL_CLEAR_FROM_CURSOR);
	rl_cursor_save_pos();
	putstr_in(line->content + line->cursor);
	rl_cursor_load_pos();
}
