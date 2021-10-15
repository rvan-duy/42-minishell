/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_check_access.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 16:36:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 16:50:11 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	safe_check_access(const char *cmd, int oflag)
{
	if (access(cmd, oflag) < 0)
	{
		if (cmd == NULL)
			ft_putstr_fd("(acces) NULL: ", 2);
		perror(cmd);
		exit(EXIT_FAILURE);
	}
}
