/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/17 15:09:23 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parse.h"
#include "envp.h"
#include "signals.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	exit_shell(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

static void	free_nodes(t_cmd_node *node)
{
	t_cmd_node	*tmp;

	while (node)
	{
		tmp = node;
		node = node->pipe_to;
		ft_free_arr((void ***)&tmp->argv);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env_var	*envp_linked;
	t_cmd_node	*node;

	envp_linked = env_arr_to_list(envp);
	while (1)
	{
		change_signals(signal_handler, SIG_IGN);
		line = readline("minishell$> ");
		signal(SIGINT, SIG_IGN);
		if (line == NULL)
			return (exit_shell());
		if (line[0] == '\0')
			continue ;
		node = parse_line(line, envp_linked);
		if (node != NULL)
		{
			execute_line(node, envp_linked);
			add_history(line);
			free(line);
		}
		free_nodes(node);
		system("leaks minishell");
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
