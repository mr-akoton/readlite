/* ========================================================================== */
/*   File    : rl_cursor.h                                                    */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 01:04:23 AM by mrakot00n                            */
/*   Updated : 2025/10/12 01:10:51 AM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_CURSOR_H__
# define __RL_CURSOR_H__

# include <stdio.h>

# include "readlite.h"

void	save_cursor_pos(void);
void	load_cursor_pos(void);
void	set_cursor_pos(size_t row, size_t col);
void	move_cursor(char direction, size_t distance);

#endif // __RL_CURSOR_H__ =================================================== */
