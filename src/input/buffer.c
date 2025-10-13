/* ========================================================================== */
/*   File    : buffer.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:14:08 AM by mrakot00n                            */
/*   Updated : 2025/10/13 12:21:00 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_input.h>
#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>

/* ========================================================================== */
/*                                    INIT                                    */
/* ========================================================================== */

void	rl_buffer_init(t_line *line)
{
	line->content = NULL;
	line->len = 0;
	line->cursor = 0;
	line->capacity = 0;
}

/* ========================================================================== */
/*                              CONTENT OPERATION                             */
/* ========================================================================== */

static int	buffer_resize(t_line *line)
{
	char	*new_ptr;

	if (line->capacity == 0 || line->len >= line->capacity * RL_BUFFER_SIZE)
	{
		line->capacity++;
		new_ptr = (char *)realloc(line->content, line->capacity * RL_BUFFER_SIZE);
		if (new_ptr == NULL)
		{
			perror("resize_buffer: realloc");
			return (-1);
		}
		line->content = new_ptr;
	}
	return (0);
}

int	rl_buffer_insert(t_line *line, char c)
{
	line->len++;

	if (buffer_resize(line) == -1)
		return (-1);
	
	// NOTE: Shift the buffer to the right if the cursor is not at
	//       the end of it before the insertion.

	if (line->cursor < line->len - 1) // Calcul is based on the current length.
		strshift(line->content, line->cursor, line->cursor + 1);
		
	line->content[line->cursor] = c;
	line->content[line->len] = RL_EOF;
	
	rl_display_buffer(line);
	line->cursor++;
	if (cursor_at_width(line->cursor))
		rl_cursor_move_down();
	else
		rl_cursor_move_by('C', 1);
	return (0);
}

void	rl_buffer_delete(t_line *line)
{
	if (line->len == 0 || line->cursor == 0)
		return ;

	// NOTE: Shift the buffer to the left if the cursor is not at the end of it
	//       before the insertion.
	//       Otherwise, will just replace the last character by eof.
	
	if (line->cursor < line->len)
		strshift(line->content, line->cursor, line->cursor - 1);
	
	line->len--;
	line->content[line->len] = RL_EOF;
	
	if (cursor_at_width(line->cursor))
		rl_cursor_move_up();
	else
		rl_cursor_move_by('D', 1);
	line->cursor--;

	rl_display_buffer(line);
}

void	rl_buffer_clear(t_line *line)
{
	if (line->content)
	{
		free(line->content);
		line->content = NULL;
	}
	line->len = 0;
	line->cursor = 0;
	line->capacity = 0;
}
