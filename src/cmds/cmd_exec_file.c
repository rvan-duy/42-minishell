/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exec_file.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:59:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/09 20:33:24 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "libft.h"
#include "safe.h"
#include "envp.h"
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>

// TODO: add error msg if executable is doens't have right permissions
// TODO: redirections if files are not NULL
// TODO: add pipes

/**
 * Creates a child process, then executes a file
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return 0 if success - 1 in case of error
 */
t_status	cmd_exec_file(t_cmd_node *nodes, t_env_var *envp)
{
	char		*absolute_path;
	char		*tmp;
	int			stat;
	pid_t		pid;

	pid = safe_fork();
	if (pid == CHILD_PROCESS)
	{
		absolute_path = cmd_get_absolute_path(nodes->cmd);
		if (absolute_path == NULL)
		{
			ft_putstr_fd(nodes->cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
		if (access(absolute_path, X_OK) < 0)
		{
			ft_putstr_fd(nodes->cmd, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			free(absolute_path);
			exit(EXIT_SUCCESS);
		}
		tmp = nodes->cmd;
		nodes->cmd = absolute_path;
		free(tmp);
		execve(nodes->cmd, nodes->argv, env_list_to_arr(envp));
		perror("execve");
		exit(EXIT_FAILURE);
	}
	wait(&stat);
	g_exit_status = WEXITSTATUS(stat);
	return (SUCCESS);
}
