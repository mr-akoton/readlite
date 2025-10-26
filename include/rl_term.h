#ifndef __RL_TERM_H__
# define __RL_TERM_H__

# include <sys/ioctl.h>
# include <termios.h>

# include <stdio.h>
# include <unistd.h>

typedef struct s_term
{
	size_t	width;
	size_t	height;
	size_t	prompt_row;
	size_t	prompt_len;
	ssize_t	cursor_col;
	ssize_t	cursor_row;
}	t_term;

extern t_term	g_tconf;

/* ========================================================================== */
/* ------------------------------- TERM MODE -------------------------------- */
/* ========================================================================== */

int	rl_enable_raw_mode(void);
int	rl_disable_raw_mode(void);

/* ========================================================================== */
/* -------------------------------- TERMINAL -------------------------------- */
/* ========================================================================== */

int	rl_term_size_update(void);

#endif // __RL_TERM_H__ ===================================================== */
