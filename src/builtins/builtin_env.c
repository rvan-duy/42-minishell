/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/14 14:52:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 15:15:51 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdio.h>

t_status	builtin_env(t_env_var *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->name, envp->value);
		envp = envp->next;
	}
	return (SUCCESS);
}
