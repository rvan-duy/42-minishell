/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_multiple_files.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:59:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 11:02:42 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "safe.h"
#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

static size_t	node_len(t_cmd_node *nodes)
{
	size_t	len;

	len = 0;
	while (nodes != NULL)
	{
		len++;
		nodes = nodes->pipe_to;
	}
	return (len);
}

static void	wait_for_all_processes(size_t node_amount, pid_t pid_last_cmd)
{
	int		exit_status;
	pid_t	pid;
	size_t	i;

	i = 0;
	while (i < node_amount)
	{
		pid = safe_wait(&exit_status);
		if (pid == pid_last_cmd)
			g_exit_status = WEXITSTATUS(exit_status);
		i++;
	}
}

static void	exec_child(int read_pipe, int write_pipe,
						t_cmd_node *nodes, t_env_var *envp)
{
	safe_dup2(read_pipe, STDIN_FILENO);
	if (read_pipe != STDIN_FILENO)
		safe_close(read_pipe);
	change_signals(SIG_DFL, SIG_DFL);
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
	const size_t	node_amount = node_len(nodes);

	previous_read_pipe = STDIN_FILENO;
	while (nodes != NULL)
	{
		pipe_fds = safe_create_pipe();
		pid = safe_fork();
		if (pid == CHILD_PROCESS)
		{
			safe_close(pipe_fds.read);
			exec_child(previous_read_pipe, pipe_fds.write, nodes, envp);
		}
		if (previous_read_pipe != STDIN_FILENO)
			safe_close(previous_read_pipe);
		if (nodes->pipe_to == NULL)
			safe_close(pipe_fds.read);
		safe_close(pipe_fds.write);
		previous_read_pipe = pipe_fds.read;
		nodes = nodes->pipe_to;
	}
	wait_for_all_processes(node_amount, pid);
}
