/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 13:26:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/24 15:42:13 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

// TODO: return value when program gets interrupted by signals!

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
		g_exit_status = 1;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("minishell$> ", STDOUT_FILENO);
		ft_putstr_fd(rl_line_buffer, STDOUT_FILENO);
		ft_putstr_fd("  \b\b", STDOUT_FILENO);
	}
}
