/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_open.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:41:06 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 10:37:58 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

int	safe_open(const char *filename, int oflag, bool in_child)
{
	int	fd;

	if (filename == NULL)
		return (-1);
	fd = open(filename, oflag, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		if (in_child == true)
			exit(EXIT_FAILURE);
		else
		{
			g_exit_status = FAILURE;
			return (-1);
		}
	}
	return (fd);
}
