/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_redirect_stdin.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 13:32:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/11 13:44:00 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "safe.h"
#include <fcntl.h>
#include <stdlib.h>

/**
 * Loops over the file array and redirects the standard input
 * @param t_files pointer to `t_cmd_node *`
 * @return Nothing, calls exit() on error
 */
void	cmd_redirect_stdin(t_files **files)
{
	int		fd;
	size_t	i;

	i = 0;
	while (files[i])
	{
		if (files[i]->e_type == REDIRECT_INPUT)
		{
			fd = safe_open(files[i]->file_name, O_RDONLY);
			safe_dup2(fd, STDIN_FILENO);
			safe_close(fd);
		}
		else if (files[i]->e_type == HERE_DOCUMENT)
		{
			// TODO
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
