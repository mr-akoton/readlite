/* ========================================================================== */
/*   File    : rl_terminal.h                                                  */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 03:05:58 PM by mrakot00n                            */
/*   Updated : 2025/10/12 01:45:47 AM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_TERMINAL_H__
# define __RL_TERMINAL_H__

# include <sys/ioctl.h>
# include <ctype.h>
# include <termios.h>
# include <stdio.h>
# include <unistd.h>

# include "readlite.h"

# define RL_REQUEST_CURSOR_POS	"\033[6n"

int	rl_enable_raw_mode(void);
int rl_disable_raw_mode(void);
int	update_terminal_settings(void);

#endif // __RL_TERMINAL__ =================================================== */
