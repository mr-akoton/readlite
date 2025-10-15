/* ========================================================================== */
/*   File    : rl_history.h                                                   */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/14 09:50:26 PM by mrakot00n                            */
/*   Updated : 2025/10/14 10:40:07 PM by mrakot00n                            */
/* ========================================================================== */

#ifndef __RL_HISTORY_H__
# define __RL_HISTORY_H__

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "readlite.h"

# define RL_HISTORY_PATH		".readlite_history"
# define RL_HISTORY_SIZE		30

typedef struct s_history
{
	char	**array;
	char	*current_line;
	size_t	size;
	size_t	index;
}	t_history;


int		rl_history_load(t_history *history);
void	rl_history_append(t_line *line);
void	rl_history_clear(t_history *history);

#endif // __RL_HISTORY_H__ ================================================== */
