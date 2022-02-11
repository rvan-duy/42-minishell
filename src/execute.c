/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:36:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/11 17:43:30 by rvan-duy      ########   odam.nl         */
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

	cmd_redirect_stdin(nodes->files);
	cmd_redirect_stdout(nodes->files);

	ret = builtin_check_and_exec(nodes, envp);
	if (ret == SUCCESS)
		exit(EXIT_SUCCESS);
	else if (ret == NO_BUILTIN)
	{
		absolute_path = cmd_get_absolute_path(nodes->cmd);
		safe_check_access(absolute_path, nodes->cmd, X_OK);
		free(nodes->argv[0]);
		nodes->argv[0] = absolute_path;
		execve(nodes->argv[0], nodes->argv, env_list_to_arr(envp));
		perror("execve");
		exit(EXIT_FAILURE);
	} 
	else if (ret == FAILURE)
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

/**
 * Reproduces the behavior of bash, the algorithm works slightly different based 
 * on whether the command has pipes or not
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return 0 if bash command has succesfully been executed - 1 in case of an error
 */
t_status	execute_line(t_cmd_node *nodes, t_env_var *envp)
{
	if (nodes->pipe_to == NULL)
	{
		cmd_exec_single_file(nodes, envp, STDOUT_FILENO);
	}
	else
	{
		handle_pipes(nodes, envp); // change to new refactored function
	}
	return (SUCCESS);
}
