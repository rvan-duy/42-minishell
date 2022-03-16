/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 13:26:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/16 16:13:08 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("minishell$> ", STDOUT_FILENO);
		ft_putstr_fd(rl_line_buffer, STDOUT_FILENO);
		ft_putstr_fd("  \n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = EXIT_FAILURE;
	}
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("\b\b\b\b>   ", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}

/**
 * Changes the handlers for SIGINT and SIGQUIT signals
 * @param sigint pointer to signal handler funct ion
 * @param sigquit pointer to signal handler function
 * @return nothing
 */
void	change_signals(void (*sigint)(int), void (*sigquit)(int))
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
