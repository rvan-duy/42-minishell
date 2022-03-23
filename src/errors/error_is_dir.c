/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_is_dir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 14:40:49 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 10:40:44 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * Checks if path is a directory, is so exits the process with exit code 127
 * @param path pointer to `char *`
 * @return nothing
 */
void	error_is_dir(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": is a directory", STDERR_FILENO);
		exit(ERROR_CODE_FOUND_BUT_NOT_EXECUTED);
	}
}
