/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_pipe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:38:29 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 12:39:02 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

t_pipefds	safe_create_pipe(void)
{
	t_pipefds	result;
	int			pipefds[2];

	if (pipe(pipefds) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	result.read = pipefds[0];
	result.write = pipefds[1];
	return (result);
}
