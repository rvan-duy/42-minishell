/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:07:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/09 14:33:39 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include <signal.h>

void	env_add(t_env_var **head, t_env_var *new)
{
	t_env_var	*tmp;

	if (new == NULL)
		kill(0, SIGSEGV);
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = env_last(*head);
	tmp->next = new;
}
