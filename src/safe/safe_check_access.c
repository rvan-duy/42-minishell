/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_check_access.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 16:36:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 10:48:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <string.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <unistd.h>

void	safe_check_access(char *absolute_path, const char *cmd, int oflag)
{
	if (access(absolute_path, oflag) < 0)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(absolute_path);
		if (errno == 2)
			exit(ERROR_CODE_NO_FILE_FOUND);
		else
			exit(ERROR_CODE_FOUND_BUT_NOT_EXECUTED);
	}
}
