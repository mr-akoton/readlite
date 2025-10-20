/* ========================================================================== */
/*   File    : history.c                                                      */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/14 09:50:17 PM by mrakot00n                            */
/*   Updated : 2025/10/20 09:45:58 AM by mrakot00n                            */
/* ========================================================================== */

#include <rl_history.h>
#include <rl_util.h>

int	rl_history_load(t_history *history)
{
	FILE	*fd;

	fd = fopen(RL_HISTORY_PATH, "r");
	if (fd == NULL)
	{
		perror("rl_history_load: fopen");
		return (-1);
	}

	history->array = (char **)calloc(RL_HISTORY_SIZE, sizeof(char *));
	if (history->array == NULL)
	{
		perror("rl_history_load: calloc");
		fclose(fd);
		return (-1);
	}

	for (size_t i = 0; i < RL_HISTORY_SIZE; i++)
	{
		history->array[i] = (char *)calloc(RL_BUFFER_SIZE + 1, sizeof(char));
		
		if (history->array[i] == NULL)
		{
			free_strarray(history->array);
			history->array = NULL;
			return (-1);
		}
		else if (fgets(history->array[i], RL_BUFFER_SIZE, fd) == NULL)
		{
			free(history->array[i]);
			history->array[i] = NULL;
			history->size = i;
			break ;
		}
	}

	history->index = history->size;
	
	fclose(fd);
	return (0);
}

void	rl_history_append(t_line *line)
{
	FILE	*fd;

	if (isempty(line->content) == 1)
		return ;

	fd = fopen(RL_HISTORY_PATH, "a");
	if (fd == NULL)
	{
		perror("rl_history_append: fopen");
		return ;
	}
	fwrite(line->content, sizeof(char), line->len, fd);
	fwrite("\n", sizeof(char), 1, fd);
	fclose(fd);
}

void	rl_history_clear(t_history *history)
{
	free_strarray(history->array);
	history->array = NULL;
}
