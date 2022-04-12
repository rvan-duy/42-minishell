/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:14:09 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/12 10:46:22 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "envp.h"
#include "safe.h"
#include "libft.h"

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

static t_status	end_function(const char *cwd, t_status exit_status)
{
	free((void *)cwd);
	g_exit_status = exit_status;
	return (exit_status);
}

t_status	builtin_cd(t_cmd_node *nodes, t_env_var *envp)
{
	t_env_var	*home_node;
	const char	*cwd = getcwd(NULL, 0);
	int			ret;

	if (nodes->argv[1] == NULL)
	{
		home_node = env_get_var("HOME", envp);
		if (home_node == NULL)
		{
			g_exit_status = FAILURE;
			return (FAILURE);
		}
		ret = safe_chdir(home_node->value);
	}
	else
		ret = safe_chdir(nodes->argv[1]);
	if (ret == FAILURE)
		return (end_function(cwd, FAILURE));
	add_cwd_to_envp(cwd, &envp);
	return (end_function(cwd, SUCCESS));
}
