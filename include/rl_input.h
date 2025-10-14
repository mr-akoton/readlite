/* ========================================================================== */
/*   File    : rl_input.h                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:12:59 AM by mrakot00n                            */
/*   Updated : 2025/10/14 09:54:14 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_INPUT_H__
# define __RL_INPUT_H__

# include <ctype.h>
# include <string.h>
# include <signal.h>

# include "readlite.h"

# define RL_EOF	0
# define RL_EOL	13
# define RL_ESC	27
# define RL_DEL 127

extern volatile sig_atomic_t	g_signal;

/* ========================================================================== */
/*                                   BUFFER                                   */
/* ========================================================================== */

void	rl_buffer_init(t_line *line);
int		rl_buffer_insert(t_line *line, char c);
void	rl_buffer_delete(t_line *line);
void	rl_buffer_clear(t_line *line);

/* ========================================================================== */
/*                                    INPUT                                   */
/* ========================================================================== */

int	rl_input_handle(char input, t_line *line);

/* ========================================================================== */
/*                                   SIGNAL                                   */
/* ========================================================================== */

int	rl_signal_setup(void);
int	rl_signal_handle(t_line *line);

#endif // __RL_INPUT_H__ ==================================================== */
