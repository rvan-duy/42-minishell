/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:36:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/27 17:20:22 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "safe.h"
#include "libft.h"
#include "builtins.h"
#include "envp.h"
#include <fcntl.h>
#include <sys/wait.h>

static int	check_builtin(t_cmd_node *nodes, t_env_var *envp)
{
	if (!ft_strncmp(nodes->cmd, "echo", ft_strlen(nodes->cmd) + 1))
		return (builtin_echo(nodes));
	if (!ft_strncmp(nodes->cmd, "pwd", ft_strlen(nodes->cmd) + 1))
		return (builtin_pwd());
	if (!ft_strncmp(nodes->cmd, "cd", ft_strlen(nodes->cmd) + 1))
		return (builtin_cd(nodes, envp));
	if (!ft_strncmp(nodes->cmd, "export", ft_strlen(nodes->cmd) + 1))
		return (builtin_export(nodes, envp));
	if (!ft_strncmp(nodes->cmd, "unset", ft_strlen(nodes->cmd) + 1))
		return (buitlin_unset(nodes, envp));
	if (!ft_strncmp(nodes->cmd, "env", ft_strlen(nodes->cmd) + 1))
		return (builtin_env(envp));
	if (!ft_strncmp(nodes->cmd, "exit", ft_strlen(nodes->cmd) + 1))
		return (builtin_exit(nodes));
	return (NO_BUILTIN);
}

/*

	cmd: grep
	argv: grep exit NULL
	pipe_to: NULL
	files:
		enum: IN
		file_name: Makefile
		enum: OUT
		file_name: grep_result

*/

#include <stdio.h>

static void	redirect_stdout(t_files **files)
{
	int		fd;
	size_t 	i;

	i = 0;
	while (files[i])
	{
		if (files[i]->e_type == REDIRECT_OUTPUT)
		{
			fd = safe_open(files[i]->file_name, O_WRONLY | O_TRUNC | O_CREAT);
			safe_dup2(fd, STDOUT_FILENO);
			safe_close(fd);
		}
		else if (files[i]->e_type == APPENDING_REDIRECT_OUTPUT)
		{
			fd = safe_open(files[i]->file_name, O_WRONLY | O_APPEND | O_CREAT);
			safe_dup2(fd, STDOUT_FILENO);
			safe_close(fd);
		}
		i++;
	}
}

static void	redirect_stdin(t_files **files)
{
	int		fd;
	size_t	i;

	i = 0;
	while (files[i])
	{
		if (files[i]->e_type == REDIRECT_INPUT)
		{
			fd = safe_open(files[i]->file_name, O_RDONLY);
			safe_dup2(fd, STDIN_FILENO);
			safe_close(fd);
		}
		else if (files[i]->e_type == HERE_DOCUMENT)
		{
			// TODO
			dprintf(2, "HERE_DOC NOT IMPLEMENTED YET\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

// Does 2< have to work aswell... ? ask marius or someone else
static void	execute_child_process(t_cmd_node node, size_t command_index, int write_fd, t_env_var *envp)
{
	(void)command_index;

	if (node.pipe_to != NULL)
	{
		safe_dup2(write_fd, STDOUT_FILENO);
		safe_close(write_fd);
	}

	redirect_stdin(node.files);
	redirect_stdout(node.files);

	safe_check_access(node.cmd, X_OK);
	execve(node.cmd, node.argv, env_list_to_arr(envp));
	
	perror("execve");
	exit(EXIT_FAILURE);
}

static void handle_processes(t_cmd_node *nodes, t_env_var *envp)
{
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
			safe_close(previous_read_pipe);
			execute_child_process(*nodes, command_index, pipe_fds.write, envp);
		}

		safe_close(pipe_fds.write);
		previous_read_pipe = pipe_fds.read;
		if (nodes->pipe_to == NULL)
			safe_close(pipe_fds.read);
		
		command_index++;
		nodes = nodes->pipe_to;
	}
	waitpid(pid, &g_exit_status, 0); // not sure if wait needs to be here of after the loop
	// close
	// wait
}

int	execute_line(t_cmd_node *nodes, t_env_var *envp)
{
	if (nodes->cmd == NULL)
		return (SUCCESS);
	// this can return -1 1 or 2 .. check that
	if (check_builtin(nodes, envp) != NO_BUILTIN)
		return (SUCCESS);
	// start_chain(nodes, envp);
	handle_processes(nodes, envp);
	return (SUCCESS);
}
