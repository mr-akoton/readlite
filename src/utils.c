/* ========================================================================== */
/*   File    : utils.c                                                        */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 04:39:04 PM by mrakot00n                            */
/*   Updated : 2025/10/12 01:46:02 AM by mrakot00n                            */
/* ========================================================================== */

#include <rl_utils.h>

/* ========================================================================== */
/*                              STRING OPERATIONS                             */
/* ========================================================================== */

void	putstr_stdin(const char *str) {
	size_t	len;

	len = strlen(str);
	if (len > 0) {
		if (write(STDIN_FILENO, str, len) == -1) {
			perror("write");
		}
	}
}

void	strshift(char *str, size_t from, size_t to) {
	void		*dst;
	const void	*src;

	src = str + from;
	dst = str + to;
	str = (char *)memmove(dst, src, strlen(src));
}

int	read_nullterm(int fd, char *buffer, size_t size) {
	ssize_t	bytesread;

	bytesread = read(fd, buffer, size);
	if (bytesread == -1) {
		perror("read");
		return (-1);
	}
	buffer[bytesread] = RL_EOF;
	return (bytesread);
}

/* ========================================================================== */
/*                              READLITE HELPERS                              */
/* ========================================================================== */

void	init_line(t_line *line) {
	line->content = NULL;
	line->cursor = 0;
	line->len = 0;
}

void	print_prompt(const char *prompt) {
	if (prompt == NULL) {
		putstr_stdin(RL_PROMPT);
	} else {
		putstr_stdin(prompt);
	}
}
