/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:04:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/01 14:52:39 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
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

static t_status	list_export(t_env_var *envp)
{
	t_env_var	*sorted_env;

	sorted_env = env_list_dup(envp);
	bubble_sort(&sorted_env);
	while (sorted_env)
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

t_status	builtin_export(t_cmd_node *nodes, t_env_var *envp)
{
	t_env_var	*new_env_var;
	size_t		i;

	if (nodes->argv[1] == NULL)
		return (list_export(envp));
	i = 1;
	while (nodes->argv[i] != NULL)
	{
		new_env_var = env_node_new(nodes->argv[i]);
		if (new_env_var == NULL)
			return (FAILURE);
		env_node_del(new_env_var->name, &envp);
		env_node_add(&envp, new_env_var);
		i++;
	}
	return (SUCCESS);
}
