/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_len.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 14:24:46 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/03 13:47:30 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

size_t	env_len(t_env_var *envp)
{
	size_t	count;

	count = 0;
	while (envp != NULL)
	{
		count++;
		envp = envp->next;
	}
	return (count);
}
