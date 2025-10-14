/* ========================================================================== */
/*   File    : input.c                                                        */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 09:32:36 AM by mrakot00n                            */
/*   Updated : 2025/10/13 12:19:01 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_input.h>
#include <rl_util.h>
#include <rl_term.h>
#include <rl_display.h>


/* ========================================================================== */
/*                             SECONDARY HANDLERS                             */
/* ========================================================================== */

static void	handle_cursor_movement(char direction, t_line *line)
{
	if (direction == 'C' && line->cursor < line->len)
	{
		line->cursor++;
		g_tconf.cursor_col++;
	}
	else if (direction == 'D' && line->cursor > 0)
	{
		line->cursor--;
		g_tconf.cursor_col--;
	}
}

static int	handle_escape_sequence(t_line *line)
{
	static char	seq[_SIZE_8];

	if (safe_read(STDIN_FILENO, seq, _SIZE_8) == -1)
		return (-1);

	if (seq[0] == '[')
	{
		if (seq[1] == 'A' || seq[1] == 'B')
			return (0);
		else if (seq[1] == 'C' || seq[1] == 'D')
			handle_cursor_movement(seq[1], line);
		else
		{
			// Unhandled sequence will fall here
			putstr_in("\033");
			putstr_in(seq);
		}
	}

	return (0);
}

/* ========================================================================== */
/*                                INPUT HANDLER                               */
/* ========================================================================== */

int	rl_input_handle(char input, t_line *line)
{
	if (input == RL_EOL)
		return (-1);
	else if (input == RL_EOF)
		return (-1);
	else if (input == RL_ESC)
		handle_escape_sequence(line);
	else if (input == RL_DEL)
		rl_buffer_delete(line);
	else if (isprint(input))
		rl_buffer_insert(line, input);
	return (0);
}
