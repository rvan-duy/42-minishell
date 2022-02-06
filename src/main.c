/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/06 16:56:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "parse.h"
#include "envp.h"
#include "builtins.h"
#include "debug.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>

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
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("minishell$> ", STDOUT_FILENO);
		ft_putstr_fd(rl_line_buffer, STDOUT_FILENO);
		ft_putstr_fd("  \b\b", STDOUT_FILENO);
	}
}

static void	init_signals(void)
{
	struct sigaction	action;

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
			if (line[0] != '\0')
			{
				parse_line(line, &node, envp);
				print_nodes(node);
				execute_line(node, envp_linked);
				add_history(line);
				free(line);
			}
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
