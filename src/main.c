/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 16:51:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/11 12:35:31 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"
#include "parse.h"
#include "envp.h"
#include "builtins.h"
#include "debug.h"
#include "signals.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

/*
sigemptyset, sigaddset, stat, lstat, fstat, unlink, opendir, readdir, closedir,
isatty, ttyname, ttyslot, ioctl,getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
*/

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
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
		if (line[0] == '\0')
			continue ;
		node = parse_line(line, envp_linked);
		if (node != NULL)
		{
			// print_nodes(node);
			execute_line(node, envp_linked);
			add_history(line);
			free(line);
		}
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
