/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_multiple_files.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:59:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/06 15:28:27 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "safe.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

static void	exec_child(int read_pipe, int write_pipe,
						t_cmd_node *nodes, t_env_var *envp)
{
	safe_dup2(read_pipe, STDIN_FILENO);
	if (read_pipe != STDIN_FILENO)
		safe_close(read_pipe);
	cmd_exec_single_file(nodes, envp, write_pipe);
	exit(EXIT_SUCCESS);
}

/**
 * Executes all files or builtins stored in nodes
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return nothing
 */
void	cmd_exec_multiple_files(t_cmd_node *nodes, t_env_var *envp)
{
	int				previous_read_pipe;
	pid_t			pid;
	t_pipefds		pipe_fds;
	size_t			command_index;
	int				exit_status;

	command_index = 0;
	previous_read_pipe = STDIN_FILENO;
	while (nodes)
	{
		pipe_fds = safe_create_pipe();
		pid = safe_fork();
		if (pid == CHILD_PROCESS)
			exec_child(previous_read_pipe, pipe_fds.write, nodes, envp);
		wait(&exit_status);
		g_exit_status = WEXITSTATUS(exit_status);
		safe_close(pipe_fds.write);
		previous_read_pipe = pipe_fds.read;
		if (nodes->pipe_to == NULL)
			safe_close(pipe_fds.read);
		command_index++;
		nodes = nodes->pipe_to;
	}
}
