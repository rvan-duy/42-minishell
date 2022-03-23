/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_chdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:42:55 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 11:48:15 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <unistd.h>
#include <stdio.h>

int	safe_chdir(const char *dir)
{
	if (chdir(dir) < 0)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		perror(dir);
		return (FAILURE);
	}
	return (SUCCESS);
}
