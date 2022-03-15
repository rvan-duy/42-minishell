/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_expand_heredoc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 12:25:57 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/15 15:06:15 by rvan-duy      ########   odam.nl         */
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

static void	do_heredoc(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			free(line);
			break ;
		}
		else if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
			ft_putendl_fd(line, fd);
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
}

static void	handle_heredoc(t_file *content)
{
	static int	number = 1;
	char		*file_name;
	int			fd;

	file_name = ft_protect(ft_strjoin("/tmp/minishell_tmp_", \
				ft_protect(ft_itoa(number))));
	fd = safe_open(file_name, O_WRONLY | O_TRUNC | O_CREAT);
	number++;
	signal(SIGINT, signal_handler_heredoc);
	do_heredoc(content->file_name, fd);
	signal(SIGINT, SIG_IGN);
	safe_close(fd);
	free(content->file_name);
	content->file_name = file_name;
}

void	expand_files(t_list *files)
{
	t_file	*content;
	
	while (files)
	{
		content = files->content;
		if (content->e_type == HERE_DOCUMENT)
		{
			handle_heredoc(files->content);
		}
		files = files->next;
	}
}

/**
 * Expands all heredocs to files
 * @param nodes pointer to `t_cmd_node *`
 */
void	cmd_expand_heredoc(t_cmd_node *nodes)
{
	while (nodes)
	{
		expand_files(nodes->files);
		nodes = nodes->pipe_to;
	}
}
