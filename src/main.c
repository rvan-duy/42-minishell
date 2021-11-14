/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 14:26:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "tests.h"
#include "envp.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_cmd_node	nodes;
	t_env_var	*envp_linked_list;

	(void)line;
	(void)argc;
	(void)argv;
	envp_linked_list = env_node_dup(envp); // Remember to check if this fails
	while (1)
	{
		line = readline("minishell$> ");
		// ft_putstr_fd("minishell$> ", 1);
		// parse_line(line, &nodes, &files);
		// init_echo_plus_n_flag(&nodes);
		// init_echo_without_n_flag(&nodes);
		nodes.argv = calloc(3, sizeof(char *));
		nodes.argv[0] = strdup("cd");
		nodes.argv[1] = strdup("./libft/../include");
		nodes.cmd = nodes.argv[0];
		// if (!ft_strncmp(line, "test", 4))
		// 	start_tests_echo(&nodes);
		execute_line(&nodes, &envp);
		printf("current dir: %s\n", getcwd(NULL, 0));
	}
	return (0);
}
