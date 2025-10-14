/* ========================================================================== */
/*   File    : rl_display.h                                                   */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 10:52:35 AM by mrakot00n                            */
/*   Updated : 2025/10/14 07:51:52 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_DISPLAY_H__
# define __RL_DISPLAY_H__

# include "readlite.h"

# define RL_DEFAULT_PROMPT		"$ "

# define RL_REQUEST_CURSOR_POS	"\033[6n"
# define RL_SAVE_CURSOR_POS		"\0337"
# define RL_LOAD_CURSOR_POS		"\0338"
# define RL_CLEAR_FROM_CURSOR	"\033[J"
# define RL_MOVE_CURSOR_NLINE 	"\033[E"
# define RL_MOVE_CURSOR_PLINE	"\033[A\033[999C"

/* ========================================================================== */
/*                                   CURSOR                                   */
/* ========================================================================== */

void	rl_cursor_save_pos(void);
void	rl_cursor_load_pos(void);
void	rl_cursor_set_pos(size_t row, size_t col);
void	rl_cursor_get_pos(size_t *row, size_t *col);
void	rl_cursor_redisplay(void);
void	rl_cursor_move_down(void);
void	rl_cursor_move_up(void);
void	rl_cursor_to_newline(t_line *line);

/* ========================================================================== */
/*                                   RENDER                                   */
/* ========================================================================== */

void	rl_display_prompt(const char *prompt);
void	rl_display_buffer(t_line *line);
void	rl_display_refresh(t_line *line);

#endif // __RL_DISPLAY_H__ ================================================== */
