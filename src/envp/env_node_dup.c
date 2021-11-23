/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_node_dup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 15:51:17 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/10 15:56:48 by rvan-duy      ########   odam.nl         */
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
	duplicate->value = ft_strdup(node->value);
	duplicate->next = NULL;
	if (duplicate->name == NULL || duplicate->value == NULL)
		return (NULL);
	return (duplicate);
}
