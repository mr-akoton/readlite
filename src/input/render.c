/* ========================================================================== */
/*   File    : render.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:28:55 AM by mrakot00n                            */
/*   Updated : 2025/10/12 10:48:49 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>

/* ========================================================================== */
/*                               PROMPT DISPLAY                               */
/* ========================================================================== */

void	rl_display_prompt(const char *prompt)
{
	size_t	col;
	size_t	row;

	if (prompt == NULL)
		putstr_in(RL_DEFAULT_PROMPT);
	else
		putstr_in(prompt);

	if (rl_cursor_get_pos(&row, &col) == -1)
		g_tconf.prompt_offset = 0;
	else
		g_tconf.prompt_offset = col;
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
