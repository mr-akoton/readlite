#include <rl_util.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* ========================================================================== */
/* -------------------------------- CHECKERS -------------------------------- */
/* ========================================================================== */

int	isempty(const char *str)
{
	if (str == NULL)
		return (1);
	for (size_t i = 0; str[i]; i++)
	{
		if (!isspace(str[i]))
			return (0);
	}
	return (1);
}

/* ========================================================================== */
/* ------------------------------- OPERATIONS ------------------------------- */
/* ========================================================================== */

void	strshift(char *str, size_t from, size_t to)
{
	size_t		src_len;
	void		*dst;
	const void	*src;

	if (str != NULL && from != to)
	{
		src = str + from;
		dst = str + to;
		src_len = strlen(src);
		if (src_len > 0)
			str = (char *)memmove(dst, src, src_len);
	}
}

void	free_strarray(char **array)
{
	if (array == NULL)
		return ;
	for (size_t i = 0; array[i] != NULL; i++)
		free(array[i]);
	free(array);
}

void	free_nstrarray(char **array, size_t n)
{
	if (array == NULL)
		return ;
	for (size_t i = 0; i < n; i++)
		free(array[i]);
	free(array);
}
