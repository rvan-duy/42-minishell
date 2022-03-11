/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_redirect_stdin.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:32:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/11 14:28:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include "libft.h"
#include "signals.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	start_heredoc(char *limiter, int fd)
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

static void	handle_redirect_input(t_files *content)
{
	int	fd;

	fd = safe_open(content->file_name, O_RDONLY);
	safe_dup2(fd, STDIN_FILENO);
	safe_close(fd);
}

static void	handle_heredoc(t_files *content)
{
	int	fd;

	fd = safe_open("/tmp/8734583475634", O_WRONLY | O_TRUNC | O_CREAT);
	signal(SIGINT, signal_handler_heredoc);
	start_heredoc(content->file_name, fd);
	signal(SIGINT, SIG_IGN);
	safe_close(fd);
	fd = safe_open("/tmp/8734583475634", O_RDONLY);
	safe_dup2(fd, STDIN_FILENO);
	safe_close(fd);
}

/**
 * Loops over the file array and redirects the standard input
 * @param t_files pointer to `t_files *`
 * @return Nothing, calls exit() on error
 */
void	cmd_redirect_stdin(t_list *files)
{
	size_t	i;
	t_files	*content;

	i = 0;
	while (files)
	{
		content = files->content;
		if (content->e_type == REDIRECT_INPUT)
			handle_redirect_input(content);
		else if (content->e_type == HERE_DOCUMENT)
			handle_heredoc(content);
		files = files->next;
	}
}
