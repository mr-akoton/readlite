/* ========================================================================== */
/*   File    : readlite.h                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 02:48:56 PM by mrakot00n                            */
/*   Updated : 2025/10/12 01:12:20 AM by mrakot00n                            */
/* ========================================================================== */

#ifndef READLITE_H
# define READLITE_H

# include <stdlib.h>

# define RL_PROMPT		"$ "
# define RL_BUFFER_SIZE	4096

# define RL_EOF		0
# define RL_EOL		13
# define RL_ESCAPE	27

typedef struct s_term {
	size_t	width;
	size_t	height;
	size_t	cursor_x;
	size_t	cursor_y;
	size_t	prompt_len;
}	t_term;

typedef struct s_line {
	char	*content;
	size_t	len;
	size_t	cursor;
}	t_line;

extern t_term	term;

char	*readlite(const char *prompt);

#endif // READLITE_H ======================================================== */
