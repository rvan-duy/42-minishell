/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_node_dup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 15:51:17 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/23 16:27:52 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

t_env_var	*env_node_dup(t_env_var *node)
{
	t_env_var	*duplicate;

	duplicate = malloc(sizeof(t_env_var));
	if (duplicate == NULL)
		return (NULL);
	duplicate->name = ft_strdup(node->name);
	if (duplicate->name == NULL)
	{
		free(duplicate);
		return (NULL);
	}
	if (node->value != NULL)
	{
		duplicate->value = ft_strdup(node->value);
		if (duplicate->value == NULL)
		{
			free(duplicate);
			free(duplicate->name);
			return (NULL);
		}
	}
	else
		duplicate->value = NULL;
	duplicate->next = NULL;
	return (duplicate);
}
