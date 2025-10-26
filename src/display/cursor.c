#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>
#include <string.h>

/* ========================================================================== */
/* ----------------------------- LOAD AND SAVE ------------------------------ */
/* ========================================================================== */

void	rl_cursor_save_pos(void)
{
	putstr_in(RL_SAVE_CURSOR_POS);
}

void	rl_cursor_load_pos(void)
{
	putstr_in(RL_LOAD_CURSOR_POS);
}

/* ========================================================================== */
/* -------------------------------- POSITION -------------------------------- */
/* ========================================================================== */

void	rl_cursor_set_pos(size_t row, size_t col)
{
	char	buffer[_SIZE_16];

	snprintf(buffer, _SIZE_16, "\033[%ld;%ldH", row, col);
	putstr_in(buffer);
}

void	rl_cursor_get_pos(size_t *row, size_t *col)
{
	char	buffer[_SIZE_16];
	
	putstr_in(RL_REQUEST_CURSOR_POS);
	*row = 0;
	*col = 0;
	if (safe_read(STDIN_FILENO, buffer, _SIZE_16) == -1)
		return ;
	*row = (size_t)atoi(&buffer[2]);
	*col = (size_t)atoi(strchr(buffer, ';') + 1);
}

void	rl_cursor_redisplay(void)
{
	if (g_tconf.cursor_col < 1)
	{
		g_tconf.cursor_row--;
		g_tconf.cursor_col = g_tconf.width + g_tconf.cursor_col;
	}
	else if (g_tconf.cursor_col > (ssize_t)g_tconf.width)
	{
		g_tconf.cursor_row++;
		g_tconf.cursor_col = g_tconf.cursor_col - g_tconf.width;
	}
	rl_cursor_set_pos(g_tconf.cursor_row, g_tconf.cursor_col);
}

/* ========================================================================== */
/* -------------------------------- MOVEMENT -------------------------------- */
/* ========================================================================== */

void	rl_cursor_move_down(void)
{
	putstr_in(RL_MOVE_CURSOR_NLINE);
	g_tconf.cursor_row++;
	g_tconf.cursor_col = 1;
}

void	rl_cursor_move_up(void)
{
	putstr_in(RL_MOVE_CURSOR_PLINE);
	g_tconf.cursor_row--;
	g_tconf.cursor_col = g_tconf.width;
}

void	rl_cursor_to_prompt(void)
{
	g_tconf.cursor_row = g_tconf.prompt_row;
	g_tconf.cursor_col = 1;
}

void	rl_cursor_to_endline(t_line *line)
{
	size_t	rows;

	rows = ((g_tconf.prompt_len + line->len) / g_tconf.width);
	g_tconf.cursor_col = ((g_tconf.prompt_len + line->len) % g_tconf.width) + 1;
	g_tconf.cursor_row = g_tconf.prompt_row + rows;
}

void	rl_cursor_to_newline(t_line *line)
{
	size_t	rows;
	size_t	cursor_row;

	rows = ((g_tconf.prompt_len + line->len) / g_tconf.width) + 1;
	cursor_row = ((g_tconf.prompt_len + line->cursor) / g_tconf.width);
	g_tconf.cursor_col = 1;
	g_tconf.cursor_row += rows - cursor_row;
}
