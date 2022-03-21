/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/21 18:20:33 by mvan-wij      ########   odam.nl         */
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

static void	free_node_file(void *_file)
{
	t_file	*file;

	file = _file;
	free(file->file_name);
	free(file);
}

static void	free_nodes(t_cmd_node *node)
{
	t_cmd_node	*tmp;

	while (node != NULL)
	{
		tmp = node->pipe_to;
		ft_lstclear(&node->files, &free_node_file);
		ft_free_arr_dim(&node->argv, 2);
		free(node);
		node = tmp;
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
			execute_line(node, envp_linked);
		add_history(line);
		free(line);
		free_nodes(node);
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
