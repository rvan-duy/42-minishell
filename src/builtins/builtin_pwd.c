/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 15:09:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 14:54:56 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_status	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("getcwd");
		return (FAILURE);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
	return (SUCCESS);
}
