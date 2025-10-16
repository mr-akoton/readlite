/* ========================================================================== */
/*   File    : rl_util.h                                                      */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:58:06 AM by mrakot00n                            */
/*   Updated : 2025/10/16 02:33:27 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_UTIL_H__
# define __RL_UTIL_H__

# include <ctype.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

# include "readlite.h"

# define _SIZE_2	2
# define _SIZE_4	4
# define _SIZE_8	8
# define _SIZE_16	16
# define _SIZE_32	32
# define _SIZE_64	64
# define _SIZE_128	128
# define _SIZE_256	256
# define _SIZE_512	512
# define _SIZE_1024	1024
# define _SIZE_2048	2048

/* ========================================================================== */
/*                                   IOMANIP                                  */
/* ========================================================================== */

void	putstr_in(const char *str);
void	putstr_out(const char *str);
void	putstr_err(const char *str);
ssize_t safe_read(int fd, char *buffer, size_t nbytes);
char	*get_file_content(const char *path);

/* ========================================================================== */
/*                                   STRING                                   */
/* ========================================================================== */

int		isempty(const char *str);
size_t	strcount_word(const char *str, char delimiter);
void	strshift(char *str, size_t from, size_t to);
void	free_strarray(char **array);
void	free_nstrarray(char **array, size_t n);

#endif // __RL_UTIL_H__ ===================================================== */
