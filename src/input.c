/* ========================================================================== */
/*   File    : input.c                                                        */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 05:50:13 PM by mrakot00n                            */
/*   Updated : 2025/10/12 01:46:27 AM by mrakot00n                            */
/* ========================================================================== */

#include <rl_utils.h>
#include <rl_input.h>
#include <rl_cursor.h>

/* ========================================================================== */
/*                                   HELPERS                                  */
/* ========================================================================== */

static int resize_line_allocation(t_line *line) {
	static size_t	size_cap = 0;
	char			*new_content;

	if (size_cap == 0 || line->len >= size_cap * RL_BUFFER_SIZE) {
		size_cap++;
		new_content = (char *)realloc(line->content, size_cap * RL_BUFFER_SIZE);
		if (new_content == NULL) {
			perror("realloc");
			return (-1);
		}
		line->content = new_content;
	}
	return (0);
}

/* ========================================================================== */
/*                                INPUT HANDLER                               */
/* ========================================================================== */

/* ----- Printable ---------------------------------------------------------- */

static void	refresh_line_display(t_line *line) {
	ssize_t	offset;

	putstr_stdin("\033[0J");
	offset = line->cursor - 1;
	if (offset < 0) {
		putstr_stdin(line->content);
	} else {
		save_cursor_pos();
		putstr_stdin(line->content + offset);
		load_cursor_pos();
		move_cursor('C', 1);
	}
}

static int	handle_printable(char input, t_line *line) {
	line->len++;
	
	if (resize_line_allocation(line) == -1) {
		return (-1);
	}
	line->content[line->len] = RL_EOF;
	
	if (line->cursor < line->len - 1) {
		strshift(line->content, line->cursor, line->cursor + 1);
	}
	line->content[line->cursor] = input;
	line->cursor++;

	refresh_line_display(line);
	return (0);
}

/* ----- ANSI Escape -------------------------------------------------------- */

static void	handle_cursor_movement(char code, t_line *line) {
	if (code == 'C' && line->cursor < line->len) {
		move_cursor(code, 1);
		line->cursor++;
		if ((line->cursor + term.prompt_len) == term.width) {
			move_cursor('E', 1);
		}
	} else if (code == 'D' && line->cursor > 0) {
		move_cursor(code, 1);
		if (line->cursor == 0) {
			move_cursor('A', 1);
			move_cursor('C', 999);
		}
		line->cursor--;
	}
}

static int	handle_ansi_escape(t_line *line) {
	static char sequence[5];

	if (read_nullterm(STDIN_FILENO, sequence, sizeof(sequence)) == -1) {
		return (-1);
	}

	if (sequence[0] == '[') {
		if (sequence[1] == 'C' || sequence[1] == 'D') {
			handle_cursor_movement(sequence[1], line);
		} else {
			// Unhandled ANCI Escape sequence fall here
			putstr_stdin("\033");
			putstr_stdin(sequence);
		}
	}
	return (0);
}

/* ----- Handle Input ------------------------------------------------------- */

int	rl_handle_input(char input, t_line *line) {
	if (input == RL_ESCAPE) {
		return (handle_ansi_escape(line));
	} else if (isprint(input)) {
		return (handle_printable(input, line));
	}
	return (0);
}
