/* ========================================================================== */
/*   File    : main.c                                                         */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 05:02:48 PM by mrakot00n                            */
/*   Updated : 2025/10/13 09:29:40 AM by mrakot00n                            */
/* ========================================================================== */

#include <readlite.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	main(void) {
	char	*line;

	// line = readline("readlite$ ");
	line = readlite("readlite$ ");
	if (line) {
		printf("Line: [%s]", line);
		free(line);
	}
	return (0);
}
