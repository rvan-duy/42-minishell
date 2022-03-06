/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_wait.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 16:32:26 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/06 16:43:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

pid_t	safe_wait(int *arg)
{
	const pid_t pid = wait(arg);

	if (pid == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
