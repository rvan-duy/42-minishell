/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_expand_heredoc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 12:25:57 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 11:03:05 by mvan-wij      ########   odam.nl         */
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

static void	do_heredoc(char *limiter, int fd)
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
	g_exit_status = WEXITSTATUS(exit_status);
}

static void	handle_heredoc(t_file *content)
{
	static int	number = 1;
	char		*file_name;
	int			fd;
	char		*file_number;

	file_number = ft_protect(ft_itoa(number));
	file_name = ft_protect(ft_strjoin("/tmp/minishell_tmp_", file_number));
	free(file_number);
	fd = safe_open(file_name, O_WRONLY | O_TRUNC | O_CREAT, true);
	number++;
	do_heredoc(content->file_name, fd);
	safe_close(fd);
	if (g_exit_status == EXIT_FAILURE)
		return ;
	free(content->file_name);
	content->file_name = file_name;
}

static void	expand_files(t_list *files)
{
	t_file	*content;

	while (files != NULL)
	{
		content = files->content;
		if (content->e_type == HERE_DOCUMENT)
		{
			handle_heredoc(files->content);
			if (g_exit_status == EXIT_FAILURE)
				return ;
		}
		files = files->next;
	}
}

/**
 * Expands all heredocs to files
 * @param nodes pointer to `t_cmd_node *`
 */
t_status	cmd_expand_heredoc(t_cmd_node *nodes)
{
	g_exit_status = EXIT_SUCCESS;
	while (nodes != NULL)
	{
		expand_files(nodes->files);
		if (g_exit_status == EXIT_FAILURE)
			return (FAILURE);
		nodes = nodes->pipe_to;
	}
	return (SUCCESS);
}
