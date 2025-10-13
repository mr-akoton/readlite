/* ========================================================================== */
/*   File    : render.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:28:55 AM by mrakot00n                            */
/*   Updated : 2025/10/13 12:07:07 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>

/* ========================================================================== */
/*                               PROMPT DISPLAY                               */
/* ========================================================================== */

void	rl_display_prompt(const char *prompt)
{
	putstr_in(prompt);
	rl_cursor_get_pos(&g_tconf.prompt_row, &g_tconf.prompt_len);
	g_tconf.prompt_len--; // Cursor position is one character after the prompt.
}

void	rl_redisplay_prompt(t_line *line)
{
	size_t	row_offset;

	row_offset = line->cursor / g_tconf.width;
	rl_cursor_move_by('F', row_offset);
	putstr_in(RL_CLEAR_FROM_CURSOR);
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
