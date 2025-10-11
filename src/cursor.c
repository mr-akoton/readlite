/* ========================================================================== */
/*   File    : cursor.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 01:04:05 AM by mrakot00n                            */
/*   Updated : 2025/10/12 01:14:13 AM by mrakot00n                            */
/* ========================================================================== */

#include <rl_utils.h>
#include <rl_cursor.h>

void	save_cursor_pos(void) {
	putstr_stdin("\0337");
}

void	load_cursor_pos(void) {
	putstr_stdin("\0338");
}

void	set_cursor_pos(size_t row, size_t col) {
	char	buffer[11];
	
	snprintf(buffer, sizeof(buffer), "\033[%ld;%ldH", row, col);
	putstr_stdin(buffer);
}

void	move_cursor(char direction, size_t distance) {
	char	buffer[7];

	snprintf(buffer, sizeof(buffer), "\033[%ld%c", distance, direction);
	putstr_stdin(buffer);
}

