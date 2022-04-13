/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_io_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 20:09:19 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/13 13:20:56 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

static int	handle_stdout(t_file *content, bool in_child)
{
	int	fd;

	fd = safe_open(content->file_name, O_WRONLY | O_TRUNC | O_CREAT, in_child);
	safe_dup2(fd, STDOUT_FILENO);
	safe_close(fd);
	return (fd);
}

static int	handle_stdout_append(t_file *content, bool in_child)
{
	int	fd;

	fd = safe_open(content->file_name, O_WRONLY | O_APPEND | O_CREAT, in_child);
	safe_dup2(fd, STDOUT_FILENO);
	safe_close(fd);
	return (fd);
}

static int	handle_stdin(t_file *content, bool in_child)
{
	int	fd;

	fd = safe_open(content->file_name, O_RDONLY, in_child);
	safe_dup2(fd, STDIN_FILENO);
	safe_close(fd);
	return (fd);
}

/**
 * Loops over the file array and redirects the stdio
 * @param t_file pointer to `t_file *`
 * @param bool in_child
 * @return nothing, calls exit() on error
 */
t_status	cmd_io_redirections(t_list *files, bool in_child)
{
	int		fd;
	t_file	*content;

	while (files != NULL)
	{
		content = files->content;
		if (content->e_type == REDIRECT_OUTPUT)
			fd = handle_stdout(content, in_child);
		else if (content->e_type == APPENDING_REDIRECT_OUTPUT)
			fd = handle_stdout_append(content, in_child);
		else if (content->e_type == REDIRECT_INPUT
			|| content->e_type == HERE_DOCUMENT)
			fd = handle_stdin(content, in_child);
		if (fd == -1)
			return (FAILURE);
		files = files->next;
	}
	return (SUCCESS);
}
