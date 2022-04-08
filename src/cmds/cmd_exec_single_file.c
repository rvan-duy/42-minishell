/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_single_file.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 13:14:29 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/08 14:02:40 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "builtins.h"
#include "safe.h"
#include "libft.h"
#include "envp.h"
#include "error.h"
#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void	execute_command(t_cmd_node *nodes, t_env_var *envp)
{
	char	*valid_path;

	valid_path = cmd_get_valid_path(nodes->cmd, envp);
	if (valid_path == NULL)
		exit(EXIT_FAILURE);
	safe_check_access(valid_path, nodes->cmd, X_OK);
	error_is_dir(valid_path);
	change_signals(SIG_DFL, SIG_DFL);
	execve(valid_path, nodes->argv, env_list_to_arr(envp));
	perror("execve");
	exit(EXIT_FAILURE);
}

/**
 * Executes a single file or builtin, in case of a file
 * it will create a child process
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return nothing, if file is executed the process is replaced
 */
void	cmd_exec_single_file(t_cmd_node *nodes, t_env_var *envp,
									int write_fd)
{
	int			ret;

	if (nodes->pipe_to != NULL)
	{
		safe_dup2(write_fd, STDOUT_FILENO);
		safe_close(write_fd);
	}
	cmd_io_redirections(nodes->files, true);
	ret = builtin_check_and_exec(nodes, envp);
	if (ret == NO_BUILTIN)
		execute_command(nodes, envp);
	exit(ret);
}
