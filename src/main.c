/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/13 15:19:47 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "tests.h"
#include <stdio.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_files		files;
	t_cmd_node	nodes;

	(void)line;
	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell$> ");
		// ft_putstr_fd("minishell$> ", 1);
		// parse_line(line, &nodes, &files);
		// init_echo_plus_n_flag(&nodes);
		// init_echo_without_n_flag(&nodes);
		nodes.argv = calloc(2, sizeof(char *));
		nodes.argv[0] = strdup("pwd");
		nodes.cmd = nodes.argv[0];
		if (!ft_strncmp(line, "test", 4))
			start_tests_echo(&nodes);
		execute_line(&nodes, &files, envp);
	}
	return (0);
}
