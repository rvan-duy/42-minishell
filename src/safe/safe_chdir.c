/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_chdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:42:55 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/08 11:26:31 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	safe_chdir(const char *dir)
{
	if (chdir(dir) < 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(dir);
	}
}
