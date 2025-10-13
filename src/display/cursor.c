/* ========================================================================== */
/*   File    : cursor.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:28:30 AM by mrakot00n                            */
/*   Updated : 2025/10/13 12:23:07 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>


/* ========================================================================== */
/*                                   CHECKER                                  */
/* ========================================================================== */

int	cursor_at_width(size_t cursor_pos)
{
	size_t	col;

	col = (g_tconf.prompt_len + cursor_pos) % g_tconf.width;
	return (col == 0);
}

/* ========================================================================== */
/*                                LOAD AND SAVE                               */
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
/*                                  MOVEMENT                                  */
/* ========================================================================== */

void	rl_cursor_set_pos(size_t row, size_t col)
{
	char	buffer[_SIZE_16];

	snprintf(buffer, _SIZE_16, "\033[%ld;%ldH", row, col);
	putstr_in(buffer);
}

void	rl_cursor_move_by(char direction, size_t distance)
{
	char	buffer[_SIZE_8];

	snprintf(buffer, _SIZE_8, "\033[%ld%c", distance, direction);
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

void	rl_cursor_move_down(void)
{
	putstr_in(RL_MOVE_CURSOR_NLINE);
}

void	rl_cursor_move_up(void)
{
	putstr_in(RL_MOVE_CURSOR_PLINE);
}

void	rl_cursor_move_new_line(t_line *line)
{
	size_t	lines;
	size_t	cursor_row;

	lines = ((g_tconf.prompt_len + line->len) / g_tconf.width) + 1;
	cursor_row = (g_tconf.prompt_len + line->cursor) / g_tconf.width;
	rl_cursor_move_by('D', 999);
	rl_cursor_move_by('B', lines - cursor_row);
}
