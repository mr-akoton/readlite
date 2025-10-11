/* ========================================================================== */
/*   File    : rl_utils.h                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 04:37:15 PM by mrakot00n                            */
/*   Updated : 2025/10/11 10:59:47 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_UTILSH__
# define __RL_UTILSH__

# include <string.h>
# include <stdio.h>
# include <unistd.h>

# include "readlite.h"

/* ----- String Operations -------------------------------------------------- */

void	putstr_fd(const char* str, int fd);
void	strshift(char *str, size_t from, size_t to);
int		read_nullterm(int fd, char *buffer, size_t size);

/* ----- Readlite Healpers -------------------------------------------------- */

void	init_line(t_line *line);
void	print_prompt(const char *prompt);
void	cursor_goto(size_t row, size_t col);

#endif // __RL_UTILSH__ ===================================================== */
