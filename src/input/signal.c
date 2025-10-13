/* ========================================================================== */
/*   File    : signal.c                                                       */
/*   Author  : mrakot00n                                                      */
/* -------------------------------------------------------------------------- */
/*   Created : 2025/10/12 11:24:47 PM by mrakot00n                            */
/*   Updated : 2025/10/13 06:58:32 PM by mrakot00n                            */
/* ========================================================================== */

#include <rl_input.h>
#include <rl_display.h>
#include <rl_term.h>
#include <rl_util.h>

volatile sig_atomic_t	g_signal = 0;

/* ========================================================================== */
/*                                SIGNAL SETUPS                               */
/* ========================================================================== */

/* ----- Signal Setups ------------------------------------------------------ */

static int	setup_signal(int sig, void (*handler)(int))
{
	struct sigaction	sa;
	
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, NULL) == -1)
	{
		perror("setup_signal: sigaction");
		return (-1);
	}
	return (0);
}

/* ----- Signal Handlers ---------------------------------------------------- */

static void	handle_sigint(int /*sig*/)
{
	g_signal = SIGINT;
}

static void	handle_sigwinch(int /*sig*/)
{
	g_signal = SIGWINCH;
}

static void	handle_sigterm(int /*sig*/)
{
	g_signal = SIGTERM;
}

static void	handle_sigcont(int /*sig*/)
{
	g_signal = SIGCONT;
}

static void	handle_sigtstp(int /*sig*/)
{
	rl_disable_raw_mode();
	putstr_out("^Z");
	rl_cursor_move_by('D', 999);
	signal(SIGTSTP, SIG_DFL);
	raise(SIGTSTP);
}

int	rl_signal_setup(void)
{
	if (setup_signal(SIGINT, &handle_sigint) == -1)
		return (-1);
	if (setup_signal(SIGWINCH, &handle_sigwinch) == -1)
		return (-1);
	if (setup_signal(SIGTERM, &handle_sigterm) == -1)
		return (-1);
	if (setup_signal(SIGTSTP, &handle_sigtstp) == -1)
		return (-1);
	if (setup_signal(SIGCONT, &handle_sigcont) == -1)
		return (-1);
	if (setup_signal(SIGQUIT, SIG_IGN) == -1)
		return (-1);
	return (0);
}

/* ========================================================================== */
/*                               SIGNAL HANDLERS                              */
/* ========================================================================== */

int	rl_signal_handle(t_line *line)
{
	switch (g_signal)
	{
		case SIGINT:
			rl_cursor_move_new_line(line);
			rl_buffer_clear(line);
			rl_display_prompt(line->prompt);
			break ;
		
		case SIGWINCH:
			rl_term_size_update();
			break ;
		
		case SIGTERM:
			rl_cursor_move_new_line(line);
			rl_buffer_clear(line);
			rl_disable_raw_mode();
			_exit(143);
			break ;
		
		case SIGCONT:
			rl_enable_raw_mode();
			rl_display_refresh(line);
			setup_signal(SIGTSTP, &handle_sigtstp);
			break ;

		default:
			break ;
	}
	g_signal = 0;
	return(0);
}
