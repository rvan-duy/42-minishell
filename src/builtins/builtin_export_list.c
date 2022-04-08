/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export_list.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 13:34:47 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/08 13:38:02 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "envp.h"
#include <stdio.h>

static void	bubble_sort(t_env_var **head)
{
	t_env_var	*current;
	t_env_var	*next;
	char		*tmp[2];

	current = *head;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (ft_strcmp(current->name, next->name) > 0)
			{
				tmp[0] = current->name;
				tmp[1] = current->value;
				current->name = next->name;
				current->value = next->value;
				next->name = tmp[0];
				next->value = tmp[1];
			}
			next = next->next;
		}
		current = current->next;
	}
}

t_status	list_export(t_env_var *envp)
{
	t_env_var	*sorted_env;

	sorted_env = env_list_dup(envp);
	bubble_sort(&sorted_env);
	while (sorted_env != NULL)
	{
		if (sorted_env->value != NULL)
			printf("declare -x %s=\"%s\"\n", sorted_env->name, sorted_env->value);
		else
			printf("declare -x %s\n", sorted_env->name);
		sorted_env = sorted_env->next;
	}
	env_list_free(sorted_env);
	return (SUCCESS);
}
