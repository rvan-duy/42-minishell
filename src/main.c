/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/30 16:59:17 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "tests.h"
#include "parse.h"
#include "envp.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env_var 	*envp_linked;
	t_cmd_node	*node;

	(void)argc;
	(void)argv;
	envp_linked = env_arr_to_list(envp);
	while (1)
	{
		line = readline("minishell$> ");
		node = NULL;
		parse_line(line, &node, envp);
		execute_line(node, envp_linked);
		add_history(line); // credits to vinnie
		free(line);
	}
	return (0);
}
