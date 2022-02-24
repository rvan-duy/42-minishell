/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_node_del.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 11:38:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/24 15:41:04 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <signal.h>
#include <stdlib.h>

static void	free_node(t_env_var **node)
{
	free((*node)->name);
	free((*node)->value);
	free((*node));
	*node = NULL;
}

void	env_node_del(const char *name, t_env_var **head)
{
	t_env_var	*tmp;
	t_env_var	*prev;

	tmp = *head;
	if (head == NULL)
		kill(0, SIGSEGV);
	if (ft_strcmp(name, tmp->name) == 0)
	{
		*head = tmp->next;
		return (free_node(&tmp));
	}
	while (tmp != NULL && ft_strcmp(name, tmp->name) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free_node(&tmp);
}
