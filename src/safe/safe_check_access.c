/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_check_access.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 16:36:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/09 15:22:01 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// Probably redundant
void	safe_check_access(const char *cmd, int oflag)
{
	if (access(cmd, oflag) < 0)
	{
		ft_putstr_fd("access: ", STDERR_FILENO);
		if (cmd == NULL)
			ft_putstr_fd("NULL: ", STDERR_FILENO);
		perror(cmd);
		exit(EXIT_FAILURE);
	}
}
