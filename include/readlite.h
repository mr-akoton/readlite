/* ========================================================================== */
/*   File    : readlite.h                                                     */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 08:50:51 AM by mrakot00n                            */
/*   Updated : 2025/10/13 10:46:54 AM by mrakot00n                            */
/* ========================================================================== */

#ifndef READLITE_H
# define READLITE_H

# include <stdlib.h>

/* ========================================================================== */
/*                                  CONSTANTS                                 */
/* ========================================================================== */

/**
 * The buffer size used for dynamic memory allocation.
 * This value determines the initial size of the buffer and will exponentially
 * increase each time the buffer becomes full, ensuring efficient memory usage.
 * 
 *  WARNING:
 *  - Never set this value below 2, as it will lead to runtime errors.
 */
# define RL_BUFFER_SIZE	4096

/* ========================================================================== */
/*                                DATA STORAGE                                */
/* ========================================================================== */

/**
 * @struct BufferInfo
 * @brief Structure to hold buffer information.
 *
 * This structure is used to manage a buffer, including its content, size, 
 * and the current position of the cursor within the buffer.
 *
 * @param prompt The prompt displayed before the line.
 * @param content The buffer itself, storing the data.
 * @param len The size of the buffer.
 * @param cursor The current position of the cursor within the buffer.
 * @param capacity The current buffer size multiplier, representing the total
 *                 allocated memory for the buffer, expanding dynamically
 *                 as required.
 */
typedef struct s_line
{
	const char	*prompt;
	char		*content;
	size_t		len;
	size_t		cursor;
	size_t		capacity;
}	t_line;

/* ========================================================================== */
/*                                  FUNCTIONS                                 */
/* ========================================================================== */

/**
 * Reads a line of input from the user, similar to the readline function.
 * Displays a visual prompt to the user and waits for input until the end of the
 * line.
 * Allocates and returns a dynamically allocated string containing the input.
 * Returns NULL on error.
 *
 * @param prompt A string representing the visual prompt to display to the user.
 *               If NULL, the default prompt "$" will be displayed.
 * @return A pointer to the dynamically allocated string containing the user
 *         input, or NULL if an error occurs.
 */
char	*readlite(const char *prompt);

#endif
