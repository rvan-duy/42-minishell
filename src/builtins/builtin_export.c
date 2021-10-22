/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:04:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/22 13:14:08 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"

t_status	builtin_export(t_cmd_node *nodes, char ***envp)
{
	const char	*new_env_var = ft_str_filter(nodes->argv[1], "\"\'");

	if (new_env_var == NULL)
		return (FAILURE);
	return (envp_add_2(envp, new_env_var));
}
