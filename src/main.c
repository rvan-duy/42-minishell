/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/03 16:22:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "parse.h"
#include "envp.h"
#include "builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>

// https://stackoverflow.com/questions/68003253/error-implicit-declaration-of-function-rl-replace-line-is-invalid-in-c99-we
// TODO: ctrl-C and ctrl-\ interrupt readline
// TODO: ctrl-C displays a new prompt on a new line -- SIGINT
// TODO: ctrl-\ does nothing ------------------------- SIGQUIT
// TODO: rl_clear_history ---------------------------- deletes all the entries of the readline history
// TODO: rl_on_new_line ------------------------------ tells readline that we moved onto a newline
// TODO: rl_replace line
// TODO: rl_redisplay -------------------------------- change what is displayed on the screen to the readline buffer

void	signal_handler(int sig)
{
	static bool is_first_time = false;

	if (sig == SIGINT)
	{
		// write(STDOUT_FILENO, "\b\b  ", 5);
		// ft_putstr_fd("\nminishell$> ", STDOUT_FILENO);
		ft_putstr_fd("\nminishell$> ", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		if (is_first_time == true)
			ft_putstr_fd("\b\b  ", STDOUT_FILENO);
		is_first_time = true;
	}
	(void)sig;
}

static void init_signals(void)
{
	struct sigaction action;

	action.sa_handler = signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env_var	*envp_linked;
	t_cmd_node	*node;

	init_signals();
	envp_linked = env_arr_to_list(envp);
	while (1)
	{
		line = readline("minishell$> ");
		node = NULL;
		if (line != NULL)
		{
			// DEBUG
			// enter -> returns a line with \0
			// dprintf(2, "line is not NULL [%s]\n", line);
			if (line[0] != '\0')
			{
				parse_line(line, &node, envp);
				execute_line(node, envp_linked);
				add_history(line);
				free(line);
			}
		}
		else
		{
			ft_putendl_fd("\b \b\b \bexit", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
