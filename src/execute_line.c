/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:36:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/08 13:39:06 by rvan-duy      ########   odam.nl         */
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

static int	*create_backup(void)
{
	int	*io_cpy;

	io_cpy = ft_protect(malloc(sizeof(int) * 2));
	io_cpy[0] = dup(STDIN_FILENO);
	io_cpy[1] = dup(STDOUT_FILENO);
	return (io_cpy);
}

static void	get_backup(int *backup)
{
	safe_close(STDIN_FILENO);
	safe_close(STDOUT_FILENO);
	safe_dup2(backup[0], STDIN_FILENO);
	safe_dup2(backup[1], STDOUT_FILENO);
	free(backup);
}

static t_status	exec_builtin(t_cmd_node *nodes, t_env_var *envp)
{
	int	*filestreams_backup;

	filestreams_backup = create_backup();
	cmd_io_redirections(nodes->files, false);
	builtin_check_and_exec(nodes, envp);
	get_backup(filestreams_backup);
	return (SUCCESS);
}

static void	remove_tmp_files(t_cmd_node *nodes)
{
	t_list	*files;
	t_file	*content;

	while (nodes != NULL)
	{
		files = nodes->files;
		while (files != NULL)
		{
			content = files->content;
			if (content->e_type == HERE_DOCUMENT)
				unlink(content->file_name);
			files = files->next;
		}
		nodes = nodes->pipe_to;
	}
}

/**
 * Reproduces the behavior of bash, the algorithm works slightly different based
 * on whether the command has pipes or not
 * @param nodes pointer to `t_cmd_node *`
 * @param envp pointer to `t_env_var *`
 * @return 0 if bash command has successfully been executed
 * - 1 in case of an error
 */
t_status	execute_line(t_cmd_node *nodes, t_env_var *envp)
{
	int			pid;

	if (cmd_expand_heredoc(nodes) == FAILURE)
		return (FAILURE);
	if (nodes->pipe_to == NULL)
	{
		if (builtin_check(nodes->cmd))
			return (exec_builtin(nodes, envp));
		else
		{
			pid = safe_fork();
			if (pid == CHILD_PROCESS)
				cmd_exec_single_file(nodes, envp, STDOUT_FILENO);
			wait(&g_exit_status);
			g_exit_status = WEXITSTATUS(g_exit_status);
			return (SUCCESS);
		}
	}
	else
		cmd_exec_multiple_files(nodes, envp);
	remove_tmp_files(nodes);
	return (SUCCESS);
}
