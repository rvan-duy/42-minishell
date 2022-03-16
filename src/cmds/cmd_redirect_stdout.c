/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_redirect_stdout.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:39:59 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/15 14:55:10 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include <fcntl.h>
#include <stdlib.h>

/**
 * Loops over the file array and redirects the standard output
 * @param t_file pointer to `t_file *`
 * @return nothing, calls exit() on error
 */
void	cmd_redirect_stdout(t_list *files)
{
	int		fd;
	size_t	i;
	t_file	*content;

	i = 0;
	while (files)
	{
		content = files->content;
		if (content->e_type == REDIRECT_OUTPUT)
		{
			fd = safe_open(content->file_name, O_WRONLY | O_TRUNC | O_CREAT);
			safe_dup2(fd, STDOUT_FILENO);
			safe_close(fd);
		}
		else if (content->e_type == APPENDING_REDIRECT_OUTPUT)
		{
			fd = safe_open(content->file_name, O_WRONLY | O_APPEND | O_CREAT);
			safe_dup2(fd, STDOUT_FILENO);
			safe_close(fd);
		}
		files = files->next;
	}
}
