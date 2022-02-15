/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_file.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:59:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/15 16:10:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "libft.h"
#include "builtins.h"
#include "safe.h"
#include "envp.h"
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>

// TODO: add error msg if executable is doens't have right permissions
// TODO: redirections if files are not NULL

static void	execute_command(t_cmd_node *nodes, t_env_var *envp)
{
	char	*absolute_path;
	char	*tmp;

	absolute_path = cmd_get_absolute_path(nodes->cmd);
	safe_check_access(absolute_path, nodes->cmd, X_OK);
	tmp = nodes->cmd;
	nodes->cmd = absolute_path;
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
 * @return 0 if success - 1 in case of error
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
		exit(EXIT_SUCCESS);
	else if (ret == NO_BUILTIN)
		execute_command(nodes, envp);
	ft_putendl_fd("Error: builtin_check_and_exec == 1", STDERR_FILENO);
	g_exit_status = FAILURE;
	return (FAILURE);
}

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
	int	i;

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

// void	cmd_exec_multiple_files(t_cmd_node *nodes, t_env_var *envp)
// {
// 	int			ret;

// 	safe_dup2(prev_fd, STDIN_FILENO);
// 	if (prev_fd != 0)
// 		safe_close(prev_fd);
// 	if (nodes->pipe_to != NULL)
// 	{
// 		safe_dup2(next_fd, STDOUT_FILENO);
// 		safe_close(next_fd);
// 	}
// 	cmd_redirect_stdin(nodes->files);
// 	cmd_redirect_stdout(nodes->files);
// 	ret = builtin_check_and_exec(nodes, envp);
// 	if (ret == SUCCESFULLY_EXECUTED_BUILTIN)
// 		exit(EXIT_SUCCESS);
// 	else if (ret == NO_BUILTIN)
// 		execute_command(nodes, envp);
// 	else if (ret == FAILURE)
// 	{
// 		ft_putendl_fd("Error: builtin_check_and_exec == 1", STDERR_FILENO);
// 		exit(EXIT_FAILURE);
// 	}
// }
