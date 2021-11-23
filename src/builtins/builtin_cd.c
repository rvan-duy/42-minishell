/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:14:09 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/13 13:01:04 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "envp.h"
#include "safe.h"

t_status	builtin_cd(t_cmd_node *nodes, t_env_var *envp)
{
	t_env_var	*home_node;

	if (nodes->argv[1] == NULL || nodes->argv[1][0] == '~')
	{
		home_node = env_get_var("HOME", envp);
		if (home_node == NULL)
			return (FAILURE);
		safe_chdir(home_node->value);
	}
	else
		safe_chdir(nodes->argv[1]);
	return (SUCCESS);
}
