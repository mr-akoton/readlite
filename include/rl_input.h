/* ========================================================================== */
/*   File    : rl_input.h                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 05:50:25 PM by mrakot00n                            */
/*   Updated : 2025/10/11 09:22:49 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_INPUT_H__
# define __RL_INPUT_H__

# include <stdio.h>

# include "readlite.h"

# define RL_ESCAPE			27
# define RL_CURSOR_UP		"\033[#A"
# define RL_CURSOR_DOWN		"\033[#B"
# define RL_CURSOR_RIGHT	"\033[#C"
# define RL_CURSOR_LEFT		"\033[#D"

int	rl_handle_input(char input, t_line *line);

#endif // __RL_INPUT_H__ ==================================================== */
