/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/01 21:10:02 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "tests.h"
#include "parse.h"
#include "envp.h"
#include "builtins.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>

// TODO: ctrl-C displays a new prompt on a new line
// TODO: ctrl-D exits the shell
// TODO: ctrl-\ does nothing

void signal_handler(int sig)
{
	// ft_putnbr_fd(sig, STDERR_FILENO);
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\b \b\b \b", 6);
		ft_putstr_fd("\nminishell$> ", STDOUT_FILENO);
	}
	else if (sig == SIGQUIT)
		exit(1);
	(void)sig;
}

// sigemptyset
// sigaddset

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env_var 	*envp_linked;
	t_cmd_node	*node;
	
	struct sigaction action;

	action.sa_handler = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);

	// signal(SIGINT, &signal_handler);
	// signal(SIGQUIT, &signal_handler);

	(void)argc;
	(void)argv;
	envp_linked = env_arr_to_list(envp);

	while (1)
	{
		line = readline("minishell$> ");
		node = NULL;
		if (line != NULL)
		{
			parse_line(line, &node, envp);
			execute_line(node, envp_linked);
			add_history(line); // credits to vinnie
			free(line);
		}
	}
	return (0);
}
