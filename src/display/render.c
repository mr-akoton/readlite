/* ========================================================================== */
/*   File    : render.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:28:55 AM by mrakot00n                            */
/*   Updated : 2025/10/21 07:51:07 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>

/* ========================================================================== */
/* ----------------------------- PROMPT DISPLAY ----------------------------- */
/* ========================================================================== */

void	rl_display_prompt(const char *prompt)
{
	putstr_in(prompt);
	rl_cursor_get_pos(&g_tconf.prompt_row, &g_tconf.prompt_len);
	g_tconf.cursor_col = g_tconf.prompt_len;
	g_tconf.cursor_row = g_tconf.prompt_row;
	g_tconf.prompt_len--;
}

/* ========================================================================== */
/* ----------------------------- BUFFER DISPLAY ----------------------------- */
/* ========================================================================== */

void	rl_display_buffer(t_line *line)
{
	putstr_in(RL_CLEAR_FROM_CURSOR);
	rl_cursor_save_pos();
	putstr_in(line->content + line->cursor);
	rl_cursor_load_pos();
}

/* ========================================================================== */
/* -------------------------------- REDISPAY -------------------------------- */
/* ========================================================================== */

void	rl_display_refresh(t_line *line)
{
	rl_display_prompt(line->prompt);
	putstr_in(line->content);
	line->cursor = line->len;
}
