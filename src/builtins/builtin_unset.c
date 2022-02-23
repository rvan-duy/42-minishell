/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 13:17:20 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/15 11:29:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"

t_status	buitlin_unset(t_cmd_node *nodes, t_env_var *envp)
{
	size_t	i;

	if (nodes->argv[1] == NULL)
	{
		g_exit_status = SUCCESS;
		return (SUCCESS);
	}
	i = 1;
	while (nodes->argv[i] != NULL)
	{
		env_node_del(nodes->argv[i], &envp);
		i++;
	}
	g_exit_status = SUCCESS;
	return (SUCCESS);
}
