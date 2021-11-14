/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:36:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 15:14:31 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "safe.h"
#include "libft.h"
#include "builtins.h"
#include "envp.h"
#include <fcntl.h>
#include <sys/wait.h>

int	g_return_value;

static void	end_chain(t_cmd_node *nodes, int fd_in, t_env_var *envp)
{
	int		fd_out;
	pid_t	pid;

	pid = safe_fork();
	if (pid == CHILD_PROCESS)
	{
		fd_out = safe_open(nodes->files[OUT]->file_name, O_WRONLY | O_CREAT | O_TRUNC);
		safe_dup2(fd_in, STDIN_FILENO);
		safe_dup2(fd_out, STDOUT_FILENO);
		safe_check_access(nodes->cmd, X_OK);
		execve(nodes->cmd, nodes->argv, env_list_to_arr(envp));
	}
	safe_close(fd_in);
	waitpid(pid, &g_return_value, 0);
}

static void	continue_chain(t_cmd_node *nodes, int fd_in, t_env_var *envp)
{
	int			i;
	pid_t		pid;
	t_pipefds	pipe_fds;

	i = 0;
	while (nodes->pipe_to != NULL)
	{
		pipe_fds = safe_create_pipe();
		pid = safe_fork();
		if (pid == CHILD_PROCESS)
		{
			safe_close(pipe_fds.read);
			safe_dup2(fd_in, STDIN_FILENO);
			safe_dup2(pipe_fds.write, STDOUT_FILENO);
			safe_check_access(nodes[i].cmd, X_OK);
			execve(nodes[i].cmd, nodes[i].argv, env_list_to_arr(envp));
		}
		safe_close(fd_in);
		safe_close(pipe_fds.write);
		waitpid(pid, &g_return_value, 0);
		fd_in = pipe_fds.read;
		i++;
	}
	end_chain(nodes, fd_in, envp);
}

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
	return (NO_BUILTIN);
}

static void	start_chain(t_cmd_node *nodes, t_env_var *envp)
{
	int			fd_in;
	pid_t		pid;
	t_pipefds	pipe_fds;

	pipe_fds = safe_create_pipe();
	pid = safe_fork();
	if (pid == CHILD_PROCESS)
	{
		safe_close(pipe_fds.read);
		fd_in = safe_open(nodes->files[IN]->file_name, O_RDONLY);
		safe_dup2(fd_in, STDIN_FILENO);
		if (nodes->pipe_to != NULL)
			safe_dup2(pipe_fds.write, STDOUT_FILENO);
		check_builtin(nodes, envp);
		safe_check_access(nodes->cmd, X_OK);
		execve(nodes->cmd, nodes->argv, env_list_to_arr(envp));
	}
	safe_close(pipe_fds.write);
	waitpid(pid, &g_return_value, 0);
	if (nodes->pipe_to != NULL)
		continue_chain(nodes, pipe_fds.read, envp);
}

int	execute_line(t_cmd_node *nodes, t_env_var *envp)
{
	// this can return -1 1 or 2 .. check that
	if (check_builtin(nodes, envp) != NO_BUILTIN)
		return (SUCCESS);
	start_chain(nodes, envp);
	return (SUCCESS);
}
