/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:36:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/23 15:45:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "safe.h"
#include "libft.h"
#include "builtins.h"
#include "envp.h"
#include "cmds.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

/**
 * Reproduces the behavior of bash, the algorithm works slightly different based
 * on whether the command has pipes or not
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return 0 if bash command has succesfully been executed 
 * - 1 in case of an error
 */
t_status	execute_line(t_cmd_node *nodes, t_env_var *envp)
{
	int	ret;
	int	pid;

	if (nodes->pipe_to == NULL)
	{
		ret = builtin_check_and_exec(nodes, envp);
		if (ret == SUCCESFULLY_EXECUTED_BUILTIN)
			return (SUCCESS);
		else if (ret == NO_BUILTIN)
		{
			pid = safe_fork();
			if (pid == CHILD_PROCESS)
				cmd_exec_single_file(nodes, envp, STDOUT_FILENO);
			wait(&g_exit_status);
			return (SUCCESS);
		}
		ft_putendl_fd("Error: builtin_check_and_exec == 1", STDERR_FILENO);
		g_exit_status = FAILURE;
	}
	else
	{
		cmd_exec_multiple_files(nodes, envp);
	}
	return (SUCCESS);
}
