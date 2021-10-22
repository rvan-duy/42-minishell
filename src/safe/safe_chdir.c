/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_chdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:42:55 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/19 17:45:40 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	safe_chdir(const char *dir)
{
	if (chdir(dir) < 0)
	{
		perror("cd");
		exit(EXIT_FAILURE);
	}
}
