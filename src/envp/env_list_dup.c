/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_dup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/14 14:35:02 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 11:03:57 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

t_env_var	*env_list_dup(t_env_var *envp)
{
	t_env_var	*dupped_list;
	t_env_var	*tmp;

	dupped_list = NULL;
	while (envp != NULL)
	{
		tmp = env_node_dup(envp);
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		env_node_add(&dupped_list, tmp);
		envp = envp->next;
	}
	return (dupped_list);
}
