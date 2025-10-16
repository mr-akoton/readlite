/* ========================================================================== */
/*   File    : getline.c                                                      */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/16 11:21:34 AM by mrakot00n                            */
/*   Updated : 2025/10/16 02:47:36 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_util.h>

char	*getline(FILE *fd)
{
	char	c;
	size_t	len;
	size_t	size;
	char	*line;
	char	*temp;

	if (fd == NULL)
		return (NULL);

	size = _SIZE_128;
	line = (char *)calloc(size, sizeof(char));
	if (line == NULL)
		return (NULL);
	
	c = fgetc(fd);
	size = 0;
	while (c != '\0' && c != '\n')
	{
		line[len] = c;
		len++;

		if (len >= size - 1)
		{
			size *= 2;
			temp = (char *)realloc(line, size);
			
			if (temp == NULL)
			{
				free(line);
				return (NULL);
			}
			
			line = temp;
		}
		c = fgetc(fd);
	}

	if (len == 0 && c == '\0')
	{
		free(line);
		return (NULL);
	}

	line[len] = '\0';
	return (line);
}
