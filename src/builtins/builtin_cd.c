/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:14:09 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/08 11:07:56 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "envp.h"
#include "safe.h"
#include "libft.h"

// OLDPWD (OLDPrintWorkingDirectory) contains 
// directory before the last cd command

static void	add_cwd_to_envp(const char *cwd, t_env_var **head)
{
	t_env_var	*new_node;
	char		*full_var_name;

	full_var_name = ft_strjoin("OLDPWD=", cwd);
	if (full_var_name == NULL)
		exit(EXIT_FAILURE);
	new_node = env_node_new(full_var_name);
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	env_node_del("OLDPWD", head);
	env_node_add(head, new_node);
}

t_status	builtin_cd(t_cmd_node *nodes, t_env_var *envp)
{
	t_env_var	*home_node;
	const char	*cwd = getcwd(NULL, 0);

	if (nodes->argv[1] == NULL || nodes->argv[1][0] == '~')
	{
		home_node = env_get_var("HOME", envp);
		if (home_node == NULL)
			return (FAILURE);
		safe_chdir(home_node->value);
	}
	else
		safe_chdir(nodes->argv[1]);
	add_cwd_to_envp(cwd, &envp);
	free((void *)cwd);
	return (SUCCESS);
}
