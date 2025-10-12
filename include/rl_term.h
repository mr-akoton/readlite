/* ========================================================================== */
/*   File    : rl_term.h                                                      */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:35:34 AM by mrakot00n                            */
/*   Updated : 2025/10/12 10:27:35 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_TERM_H__
# define __RL_TERM_H__

# include <sys/ioctl.h>
# include <termios.h>

# include <ctype.h>
# include <stdio.h>
# include <unistd.h>

# include "readlite.h"

typedef struct s_term
{
	size_t	width;
	size_t	height;
	size_t	prompt_offset;
}	t_term;

extern t_term	g_tconf;

/* ========================================================================== */
/*                                  TERM MODE                                 */
/* ========================================================================== */

int	rl_enable_raw_mode(void);
int	rl_disable_raw_mode(void);

/* ========================================================================== */
/*                                  TERMINAL                                  */
/* ========================================================================== */

int	rl_term_config_update(void);


#endif // __RL_TERM_H__ ===================================================== */
