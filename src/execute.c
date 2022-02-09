/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:36:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/09 20:27:15 by rvan-duy      ########   odam.nl         */
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

/**
 * Checks if the node is a builtin command, if so: executes it
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return 0 if success - 1 in case of error - 2 if node is not a builtin command
 */
static int	builtin_check_and_exec(t_cmd_node *nodes, t_env_var *envp)
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
	if (files[i] == NULL)
		dprintf(2, "files is NULL\n");
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
	if (files[i] == NULL)
		dprintf(2, "files is NULL\n");
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

// absolute path /home/bin/cat
// relative path ../bin/cat
// Does 2< have to work aswell... ?
// TODO: IF ONLY 1 COMMAND DONT MAKE A CHILD, EXIT WONT WORK !!!!!!!!!!
static void	execute_child_process(t_cmd_node *nodes, int write_fd, t_env_var *envp)
{
	int ret;
	char *absolute_path;

	if (nodes->pipe_to != NULL)
	{
		safe_dup2(write_fd, STDOUT_FILENO);
		safe_close(write_fd);
	}

	redirect_stdin(nodes->files);
	redirect_stdout(nodes->files);

	ret = builtin_check_and_exec(nodes, envp);
	if (ret == EXECUTE_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (ret == NO_BUILTIN)
	{
		absolute_path = cmd_get_absolute_path(nodes->cmd);
		dprintf(STDERR_FILENO, "%s\n", nodes->argv[0]);
		safe_check_access(absolute_path, X_OK);
		dprintf(STDERR_FILENO, "%s\n", nodes->argv[0]);
		free(nodes->argv[0]);
		nodes->argv[0] = absolute_path;
		dprintf(STDERR_FILENO, "%s\n", nodes->argv[0]);
		execve(nodes->argv[0], nodes->argv, env_list_to_arr(envp));
		dprintf(STDERR_FILENO, "%s\n", nodes->argv[0]);
		perror("execve");
		exit(EXIT_FAILURE);
	} 
	else if (ret == EXECUTE_FAILURE)
	{
		ft_putendl_fd("builtin_check_and_exec returned 1", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void handle_pipes(t_cmd_node *nodes, t_env_var *envp)
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
			if (previous_read_pipe != 0)
				safe_close(previous_read_pipe);
			execute_child_process(nodes, pipe_fds.write, envp);
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

t_status	execute_line(t_cmd_node *nodes, t_env_var *envp)
{
	if (nodes->pipe_to == NULL)
	{
		if (NO_BUILTIN == builtin_check_and_exec(nodes, envp))
		{
			// execute command + creating child
			return (SUCCESS);
		}
	}
	else
		handle_pipes(nodes, envp);
	return (SUCCESS);
}

// int	execute_line(t_cmd_node *nodes, t_env_var *envp)
// {
// 	const int is_builtin = builtin_check_and_exec(nodes, envp);
	
// 	if (is_builtin == NO_BUILTIN)
// 	{
// 		if (nodes->cmd != NULL)
// 			handle_processes(nodes, envp);
// 		return (SUCCESS);
// 	}
// 	else if (is_builtin == ERROR)
// 	{
// 		ft_putendl_fd("error: builtin_check_and_exec returned ERROR", STDERR_FILENO);
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }
