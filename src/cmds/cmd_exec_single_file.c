/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_single_file.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 13:14:29 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/19 13:21:40 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"// cmd funcs
#include "builtins.h" // builtin funcs
#include "safe.h" // safe funcs
#include "libft.h" // putendl
#include "envp.h" // env funcs
#include "error.h" // error funcs
#include <unistd.h> // defines
#include <stdio.h> // perror

static void	execute_command(t_cmd_node *nodes, t_env_var *envp)
{
	char	*valid_path;
	char	*tmp;

	valid_path = cmd_get_valid_path(nodes->cmd);
	if (valid_path == NULL)
		exit(EXIT_FAILURE);
	safe_check_access(valid_path, nodes->cmd, X_OK);
	error_is_dir(valid_path);
	tmp = nodes->cmd;
	nodes->cmd = valid_path;
	free(tmp);
	execve(nodes->cmd, nodes->argv, env_list_to_arr(envp));
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

	if (nodes->pipe_to)
	{
		safe_dup2(write_fd, STDOUT_FILENO);
		safe_close(write_fd);
	}
	cmd_redirect_stdin(nodes->files);
	cmd_redirect_stdout(nodes->files);
	ret = builtin_check_and_exec(nodes, envp);
	if (ret == SUCCESFULLY_EXECUTED_BUILTIN)
		return ;
	else if (ret == NO_BUILTIN)
		execute_command(nodes, envp);
	ft_putendl_fd("Error: builtin_check_and_exec == 1", STDERR_FILENO);
	g_exit_status = FAILURE;
}