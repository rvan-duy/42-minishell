/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_expand_heredoc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 12:25:57 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/29 14:18:01 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include "signals.h"
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	exit_heredoc(char *line)
{
	free(line);
	exit(EXIT_SUCCESS);
}

static int	do_heredoc(char *limiter, int fd)
{
	char	*line;
	pid_t	pid;
	int		exit_status;

	pid = safe_fork();
	if (pid == 0)
	{
		signal(SIGINT, signal_handler_heredoc);
		while (true)
		{
			line = readline("> ");
			if (line == NULL)
				exit_heredoc(line);
			else if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
				ft_putendl_fd(line, fd);
			else
				exit_heredoc(line);
			free(line);
		}
	}
	safe_wait(&exit_status);
	return (WEXITSTATUS(exit_status));
}

static int	handle_heredoc(t_file *content)
{
	static int	number = 1;
	int			fd;
	int			ret;
	char		*file_name;
	char		*file_number;

	file_number = ft_protect(ft_itoa(number));
	file_name = ft_protect(ft_strjoin("/tmp/minishell_tmp_", file_number));
	free(file_number);
	fd = safe_open(file_name, O_WRONLY | O_TRUNC | O_CREAT, true);
	number++;
	ret = do_heredoc(content->file_name, fd);
	safe_close(fd);
	if (ret == EXIT_FAILURE)
		return (ret);
	free(content->file_name);
	content->file_name = file_name;
	return (ret);
}

static t_status	expand_files(t_list *files)
{
	t_file	*content;

	while (files != NULL)
	{
		content = files->content;
		if (content->e_type == HERE_DOCUMENT)
		{
			if (handle_heredoc(files->content) == EXIT_FAILURE)
			{
				g_exit_status = EXIT_FAILURE;
				return (FAILURE);
			}
		}
		files = files->next;
	}
	return (SUCCESS);
}

/**
 * Expands all heredocs to files
 * @param nodes pointer to `t_cmd_node *`
 */
t_status	cmd_expand_heredoc(t_cmd_node *nodes)
{
	while (nodes != NULL)
	{
		if (expand_files(nodes->files) == FAILURE)
			return (FAILURE);
		nodes = nodes->pipe_to;
	}
	return (SUCCESS);
}
