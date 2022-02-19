/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_dup2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:41:54 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/19 13:53:08 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Safely dups fildes1 to fildes2
 * @param fildes1 int containing a fd
 * @param fildes2 int containing a fd
 * @return nothing
 */
void	safe_dup2(int fildes1, int fildes2)
{
	if (fildes1 < 0 || fildes2 < 0 || fildes1 == fildes2)
		return ;
	if (dup2(fildes1, fildes2) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}
