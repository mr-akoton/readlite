#include <rl_util.h>
#include <string.h>
#include <stdio.h>

/* ========================================================================== */
/* -------------------------------- WRITING --------------------------------- */
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

void	putstr_out(const char *str)
{
	size_t	len;

	if (str != NULL)
	{
		len = strlen(str);
		if (len != 0)
		{
			if (write(STDOUT_FILENO, str, len) == -1)
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
/* -------------------------------- READING --------------------------------- */
/* ========================================================================== */

ssize_t safe_read(int fd, char *buffer, size_t nbytes)
{
	ssize_t	bytesread;

	bytesread = read(fd, buffer, nbytes - 1);
	if (bytesread == -1)
		perror("safe_read: read");
	else
		buffer[bytesread] = '\0';
	return bytesread;
}
