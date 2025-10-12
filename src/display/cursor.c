/* ========================================================================== */
/*   File    : cursor.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:28:30 AM by mrakot00n                            */
/*   Updated : 2025/10/12 09:46:54 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_display.h>
#include <rl_util.h>

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

int	rl_cursor_get_pos(size_t *row, size_t *col)
{
	char	buffer[_SIZE_16];
	
	putstr_in(RL_REQUEST_CURSOR_POS);
	if (safe_read(STDIN_FILENO, buffer, _SIZE_16) == -1)
		return (-1);
	*row = (size_t)atoi(&buffer[2]);
	*col = (size_t)atoi(strchr(buffer, ';') + 1);
	return (0);
}
