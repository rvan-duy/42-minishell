/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_conversion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 11:50:57 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/12 12:09:33 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <sys/wait.h>

int	signal_conversion(int exit_status)
{
	if (WIFSIGNALED(exit_status) > 0)
		return (WTERMSIG(exit_status) + 128);
	return (WEXITSTATUS(exit_status));
}
