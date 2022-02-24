/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_redirect_stdin.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:32:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/24 15:21:37 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

// ft_putstr_fd("Warning: here-document delimited by end-of-file", 2);
// ft_putstr_fd(" (wanted '", STDERR_FILENO);
// ft_putstr_fd(limiter, STDERR_FILENO);
// ft_putendl_fd("')", STDERR_FILENO);
static void	start_heredoc(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
			ft_putendl_fd(line, fd);
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
}

/**
 * Loops over the file array and redirects the standard input
 * @param t_files pointer to `t_files *`
 * @return Nothing, calls exit() on error
 */
void	cmd_redirect_stdin(t_list *files)
{
	int		fd;
	size_t	i;
	t_files	*content;

	i = 0;
	while (files)
	{
		content = files->content;
		if (content->e_type == REDIRECT_INPUT)
		{
			fd = safe_open(content->file_name, O_RDONLY);
			safe_dup2(fd, STDIN_FILENO);
			safe_close(fd);
		}
		else if (content->e_type == HERE_DOCUMENT)
		{
			fd = safe_open("/tmp/8734583475634", O_WRONLY | O_TRUNC | O_CREAT);
			start_heredoc(content->file_name, fd);
			safe_close(fd);
			fd = safe_open("/tmp/8734583475634", O_RDONLY);
			safe_dup2(fd, STDIN_FILENO);
			safe_close(fd);
		}
		files = files->next;
	}
}
