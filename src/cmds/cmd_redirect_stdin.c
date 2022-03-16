/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_redirect_stdin.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:32:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/15 15:16:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include "libft.h"
#include "signals.h"
#include <fcntl.h>
#include <stdlib.h>

static void	handle_redirect_input(t_file *content)
{
	int	fd;

	fd = safe_open(content->file_name, O_RDONLY);
	safe_dup2(fd, STDIN_FILENO);
	safe_close(fd);
}

/**
 * Loops over the file array and redirects the standard input
 * @param t_file pointer to `t_file *`
 * @return Nothing, calls exit() on error
 */
void	cmd_redirect_stdin(t_list *files)
{
	size_t	i;
	t_file	*content;

	i = 0;
	while (files)
	{
		content = files->content;
		if (content->e_type == REDIRECT_INPUT
			|| content->e_type == HERE_DOCUMENT)
			handle_redirect_input(content);
		files = files->next;
	}
}
