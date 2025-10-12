/* ========================================================================== */
/*   File    : string.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:57:13 AM by mrakot00n                            */
/*   Updated : 2025/10/12 09:46:03 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_util.h>

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
		if (src_len > 0) {
			str = (char *)memmove(dst, src, src_len);
		}
	}
}
