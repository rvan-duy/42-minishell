/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 11:38:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/02 14:19:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"

static void	free_node(t_env_var *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	env_del(const char *name, t_env_var *envp)
{
	const size_t	len = ft_strlen(name);
	t_env_var		**cur;
	t_env_var		*tmp;

	cur = &envp;
	while (*cur != NULL)
	{
		if (!ft_strncmp(name, (*cur)->name, len))
		{
			tmp = (*cur)->next;
			free_node(*cur);
			*cur = tmp;
			break ;
		}
		cur = &(*cur)->next;
	}
}
