/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_multiple_files.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:59:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/19 13:25:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "safe.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

static size_t	node_len(t_cmd_node *nodes)
{
	size_t	len;

	len = 0;
	while (nodes)
	{
		len++;
		nodes = nodes->pipe_to;
	}
	return (len);
}

static void	wait_for_all_processes(size_t node_amount)
{
	size_t	i;

	i = 0;
	while (i < node_amount)
	{
		wait(&g_exit_status);
		i++;
	}
}

/**
 * Executes all files or builtins stored in nodes
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return Nothing, calls exit() on error
 */
void	cmd_exec_multiple_files(t_cmd_node *nodes, t_env_var *envp)
{
	const size_t	node_amount = node_len(nodes);
	int				previous_read_pipe;
	pid_t			pid;
	t_pipefds		pipe_fds;
	size_t			command_index;

	command_index = 0;
	previous_read_pipe = STDIN_FILENO;
	while (nodes)
	{
		pipe_fds = safe_create_pipe();
		pid = safe_fork();
		if (pid == CHILD_PROCESS)
		{
			safe_dup2(previous_read_pipe, STDIN_FILENO);
			if (previous_read_pipe != STDIN_FILENO)
				safe_close(previous_read_pipe);
			cmd_exec_single_file(nodes, envp, pipe_fds.write);
			exit(EXIT_SUCCESS);
		}
		safe_close(pipe_fds.write);
		previous_read_pipe = pipe_fds.read;
		if (nodes->pipe_to == NULL)
			safe_close(pipe_fds.read);
		command_index++;
		nodes = nodes->pipe_to;
	}
	wait_for_all_processes(node_amount);
}
