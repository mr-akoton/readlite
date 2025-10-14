/* ========================================================================== */
/*   File    : history.c                                                      */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/14 09:50:17 PM by mrakot00n                            */
/*   Updated : 2025/10/14 10:43:44 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_history.h>
#include <rl_util.h>

int	rl_history_load(const char *path, t_history *history)
{
	size_t	size;
	FILE	*fd;

	fd = fopen(path, "w+");
	if (fd == NULL)
	{
		perror("rl_history_load: open");
		return (-1);
	}

	history->array = (char **)calloc(RL_HISTORY_SIZE, sizeof(char *));
	if (history->array == NULL)
	{
		perror("rl_history_load: calloc");
		fclose(fd);
		return (-1);
	}

	for (int i = 0; i < RL_HISTORY_SIZE; i++)
	{
		history->array[i] = (char *)calloc(RL_HISTORY_BUFFSIZE, sizeof(char));
		if (history->array[i] == NULL)
		{
			perror("rl_history_load: calloc");
			free_array(history->array, i);
			history->array = NULL;
			fclose(fd);
			return (-1);
		}
		if (fgets(history->array[i], RL_HISTORY_BUFFSIZE, fd) == NULL)
		{
			free(history->array[i]);
			size = i - 1;
			break ;
		}
	}

	history->current_line = NULL;
	history->size = size;
	history->index = size - 1;

	fclose(fd);
	return (0);
}

void	rl_history_save(const char *path, t_history *history)
{
	FILE *fd;

	fd = fopen(path, "w");
	if (fd == NULL)
	{
		perror("rl_history_save: open");
		free_array(history->array, history->size);
		if (history->current_line != NULL)
			free(history->current_line);
		return ;
	}

	for (int i = 0; i < RL_HISTORY_SIZE; i++)
	{
		if (history->array[i] != NULL)
			fwrite(history->array[i], sizeof(char), RL_HISTORY_BUFFSIZE, fd);
	}
	
	free_array(history->array, history->size);
	if (history->current_line != NULL)
		free(history->current_line);
	
	fclose(fd);
}