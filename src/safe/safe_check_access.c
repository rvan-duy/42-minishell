/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_check_access.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 16:36:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/17 16:31:26 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	safe_check_access(char *absolute_path, const char *cmd, int oflag)
{
	if (access(absolute_path, oflag) < 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		free(absolute_path);
		exit(EXIT_SUCCESS);
	}
}
