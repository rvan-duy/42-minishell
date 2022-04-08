/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:04:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/08 12:29:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include "builtins.h"
#include <stdio.h>
#include <unistd.h>

static void	bubble_sort(t_env_var **head)
{
	t_env_var	*current;
	t_env_var	*next;
	char		*tmp[2];

	current = *head;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (ft_strcmp(current->name, next->name) > 0)
			{
				tmp[0] = current->name;
				tmp[1] = current->value;
				current->name = next->name;
				current->value = next->value;
				next->name = tmp[0];
				next->value = tmp[1];
			}
			next = next->next;
		}
		current = current->next;
	}
}

static t_status	list_export(t_env_var *envp)
{
	t_env_var	*sorted_env;

	sorted_env = env_list_dup(envp);
	bubble_sort(&sorted_env);
	while (sorted_env != NULL)
	{
		if (sorted_env->value != NULL)
			printf("declare -x %s=\"%s\"\n", sorted_env->name, sorted_env->value);
		else
			printf("declare -x %s\n", sorted_env->name);
		sorted_env = sorted_env->next;
	}
	env_list_free(sorted_env);
	return (SUCCESS);
}

static int	check_valid_identifier(char *identifier)
{
	size_t	i;

	if (ft_isalpha(identifier[0]) == 0)
		return (INVALID);
	i = 0;
	while (identifier[i] != '\0')
	{
		if (ft_isalnum(identifier[i]) == 0 && identifier[i] != '_')
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

t_status	builtin_export(t_cmd_node *nodes, t_env_var *envp)
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
		if (check_valid_identifier(new_env_var->name) == INVALID)
		{
			print_identifier_error(new_env_var);
			free(new_env_var);
		}
		else if (env_get_var(new_env_var->name, envp) == NULL)
			env_node_add(&envp, new_env_var);
		else if (env_get_var(new_env_var->name, envp) != NULL && new_env_var->value != NULL)
		{
			env_node_del(new_env_var->name, &envp);
			env_node_add(&envp, new_env_var);
		}
		i++;
	}
	return (SUCCESS);
}
