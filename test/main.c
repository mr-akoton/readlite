/* ========================================================================== */
/*   File    : main.c                                                         */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 05:02:48 PM by mrakot00n                            */
/*   Updated : 2025/10/11 05:31:07 PM by mrakot00n                            */
/* ========================================================================== */

#include <readlite.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void) {
	char	*line;

	line = readlite("readline$ ");
	if (line) {
		printf("Line: [%s]", line);
		free(line);
	}
	return (0);
}