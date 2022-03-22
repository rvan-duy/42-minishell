/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_close.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:39:29 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/22 19:38:44 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

void	safe_close(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": Close (fd: ", STDERR_FILENO);
		ft_putnbr_fd(fd, STDERR_FILENO);
		ft_putendl_fd(")", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
