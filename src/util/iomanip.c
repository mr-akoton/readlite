/* ========================================================================== */
/*   File    : iomanip.c                                                      */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:57:11 AM by mrakot00n                            */
/*   Updated : 2025/10/12 10:30:29 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_util.h>

/* ========================================================================== */
/*                                   WRITING                                  */
/* ========================================================================== */

void	putstr_in(const char *str)
{
	size_t	len;

	if (str != NULL)
	{
		len = strlen(str);
		if (len != 0)
		{
			if (write(STDIN_FILENO, str, len) == -1)
				perror("putstr: write");
		}
	}
}

void	putstr_err(const char *str)
{
	size_t	len;

	if (str != NULL)
	{
		len = strlen(str);
		if (len != 0)
		{
			if (write(STDERR_FILENO, str, len) == -1)
				perror("putstr: write");
		}
	}
}

/* ========================================================================== */
/*                                   READING                                  */
/* ========================================================================== */

ssize_t safe_read(int fd, char *buffer, size_t nbytes)
{
	ssize_t	bytesread;

	bytesread = read(fd, buffer, nbytes);
	if (bytesread == -1)
		perror("safe_read: read");
	else
		buffer[bytesread] = '\0';
	return bytesread;
}
