/* ========================================================================== */
/*   File    : input.c                                                        */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/11 05:50:13 PM by mrakot00n                            */
/*   Updated : 2025/10/11 11:56:20 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_utils.h>
#include <rl_input.h>


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

static void	display_line(t_line *line) {
	(void)line;
	putstr_fd("\033[0J", STDIN_FILENO);
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

	display_line(line);
	return (0);
}

/* ----- ANSI Escape -------------------------------------------------------- */

static void	move_cursor(char code, t_line *line) {
	if (code == 'C' && line->cursor <= line->len) {
		putstr_fd(RL_CURSOR_RIGHT, STDIN_FILENO);
		
		line->cursor++;
		term.cursor_x++;
		
		if (term.cursor_x == term.width) {
			term.cursor_y++;
			term.cursor_x = 0;
			cursor_goto(term.cursor_y, term.cursor_x);
		}
	} else if (code == 'D' && line->cursor > 0) {
		putstr_fd(RL_CURSOR_LEFT, STDIN_FILENO);
		
		line->cursor--;
		term.cursor_x--;
		
		if (term.cursor_x == 0) {
			term.cursor_y--;
			term.cursor_x = term.width;
			cursor_goto(term.cursor_y, term.cursor_x);
		}
	}
}

static int	handle_ansi_escape(t_line *line) {
	static char sequence[5];

	if (read_nullterm(STDIN_FILENO, sequence, sizeof(sequence)) == -1) {
		return (-1);
	}

	if (sequence[0] == '[') {
		if (sequence[1] == 'C' || sequence[1] == 'D') {
			move_cursor(sequence[1], line);
		} else {
			// Unhandled ANCI Escape sequence fall here
			putstr_fd("\033", STDIN_FILENO);
			putstr_fd(sequence, STDIN_FILENO);
		}
	}
	return (0);
}

/* ----- Handle Input ------------------------------------------------------- */

int	rl_handle_input(char input, t_line *line) {
	if (input == RL_ESCAPE) {
		return (handle_ansi_escape(line));
	} else {
		return (handle_printable(input, line));
	}
	return (0);
}