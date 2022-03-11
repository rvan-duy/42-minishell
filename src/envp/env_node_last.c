/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_node_last.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 14:13:58 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/11 14:35:44 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

t_env_var	*env_node_last(t_env_var *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}
