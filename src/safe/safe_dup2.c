/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup2.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:41:54 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 12:42:31 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	safe_dup2(int fildes1, int fildes2)
{
	if (fildes1 < 0 || fildes2 < 0)
		return ;
	if (dup2(fildes1, fildes2) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}
