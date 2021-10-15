/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_open.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:41:06 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 13:45:52 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	safe_open(const char *filename, int oflag)
{
	int	fd;

	if (filename == NULL)
		return (-1);
	fd = open(filename, oflag, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
