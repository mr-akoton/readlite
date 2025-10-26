#include <rl_input.h>
#include <rl_util.h>
#include <rl_term.h>
#include <rl_history.h>
#include <rl_display.h>

/* ========================================================================== */
/* --------------------------- SECONDARY HANDLERS --------------------------- */
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

static void	handle_history_navigation(char direction, t_line *line,
									  t_history *history)
{
	if (direction == 'A' && history->index != 0)
	{
		if (history->index == history->size)
			history->current_line = line->content;

		history->index--;
		line->content = history->array[history->index];
	}
	else if (direction == 'B' && history->index < history->size)
	{
		history->index++;
		if (history->index == history->size)
			line->content = history->current_line;
		else 
			line->content = history->array[history->index];
	}
	else
		return ;

	line->len = strlen(line->content);
	rl_cursor_to_prompt();
	rl_cursor_redisplay();
	putstr_in(RL_CLEAR_FROM_CURSOR);
	rl_display_refresh(line);
	rl_cursor_to_endline(line);
}

static int	handle_escape_sequence(t_line *line, t_history *history)
{
	static char	seq[_SIZE_8];

	if (safe_read(STDIN_FILENO, seq, _SIZE_8) == -1)
		return (-1);

	if (seq[0] == '[')
	{
		if (seq[1] == 'A' || seq[1] == 'B')
			handle_history_navigation(seq[1], line, history);
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
/* ----------------------------- INPUT HANDLER ------------------------------ */
/* ========================================================================== */

int	rl_input_handle(char input, t_line *line, t_history *history)
{
	if (input == RL_EOL)
		return (-1);
	else if (input == RL_EOF)
		return (-1);
	else if (input == RL_ESC)
		handle_escape_sequence(line, history);
	else if (input == RL_DEL)
		rl_buffer_delete(line);
	else if (isprint(input))
		rl_buffer_insert(line, input);
	return (0);
}
