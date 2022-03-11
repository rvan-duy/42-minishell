/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_len.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 14:24:46 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/11 14:35:27 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

size_t	env_list_len(t_env_var *envp)
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
