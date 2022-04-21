/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:04:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/21 15:04:58 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include "builtins.h"
#include <unistd.h>

static int	check_valid_identifier(char *identifier)
{
	size_t	i;

	if (ft_isdigit(identifier[0]))
		return (INVALID);
	i = 0;
	while (identifier[i] != '\0')
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (INVALID);
		i++;
	}
	return (VALID);
}

static void	print_identifier_error(t_env_var *var)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(var->name, STDERR_FILENO);
	ft_putstr_fd("=", STDERR_FILENO);
	ft_putstr_fd(var->value, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_exit_status = FAILURE;
}

static void	add_node(t_env_var *new_env_var, t_env_var **envp)
{
	if (check_valid_identifier(new_env_var->name) == INVALID)
	{
		print_identifier_error(new_env_var);
		free(new_env_var);
	}
	else if (env_get_var(new_env_var->name, *envp) == NULL)
		env_node_add(envp, new_env_var);
	else if (env_get_var(new_env_var->name, *envp) != NULL
		&& new_env_var->value != NULL)
	{
		env_node_del(new_env_var->name, envp);
		env_node_add(envp, new_env_var);
	}
}

t_status	builtin_export(t_cmd_node *nodes, t_env_var **envp)
{
	t_env_var	*new_env_var;
	size_t		i;

	g_exit_status = SUCCESS;
	if (nodes->argv[1] == NULL)
		return (list_export(envp));
	i = 1;
	while (nodes->argv[i] != NULL)
	{
		new_env_var = env_node_new(nodes->argv[i]);
		if (new_env_var == NULL)
			return (FAILURE);
		add_node(new_env_var, envp);
		i++;
	}
	return (SUCCESS);
}
