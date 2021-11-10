/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:04:28 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/10 16:34:32 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include <stdio.h>

// If env var already exist, replace it
// export without args
// export can have multiple thingys

static void	swap_ele(char **ptr1, char **ptr2)
{
	char	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void	bubble_sort(char **envp, size_t envp_len)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (i < envp_len - 1)
	{
		j = 0;
		while (j < envp_len - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], \
				ft_strchr(envp[j], '=') - envp[j]) > 0)
				swap_ele(&envp[j], &envp[j + 1]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < envp_len)
	{
		printf("declare -x \"%s\"\n", envp[i]);
		i++;
	}
}

static void	env_add_before(t_env_var **head, t_env_var *new)
{
	if (!*head)
	{
		*head = new;
		return ;
	}
	new->next = *head;
	*head = new;
}

static void	env_add_inbetween(t_env_var *prev, t_env_var *new)
{
	new->next = prev->next;
	prev->next = new;
}

static void	sortedstack_add(t_env_var **head, t_env_var *new)
{
	t_env_var	*tmp;

	tmp = *head;
	if (!tmp)
		env_add(head, new);
	while (tmp)
	{
		if (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				env_add_inbetween(tmp, new);
				return ;
			}
		}
		else if (tmp && !tmp->next)
		{
			if (ft_strcmp(tmp->name, new->name) > 0)
				env_add(head, new);
			else
				env_add_before(head, new);
			return ;
		}
		tmp = tmp->next;
	}
}

// TODO: malloc protect and proper free
static t_env_var	*get_sorted_list(t_env_var *envp)
{
	t_env_var	*sorted_list;
	t_env_var	*tmp;

	while (envp)
	{
		tmp = env_dup(envp);
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		sortedstack_add(&sorted_list, tmp);
		envp = envp->next;
	}
	return (sorted_list);
}

static t_status	list_export(t_env_var *envp)
{
	t_env_var	*sorted_envp;

	sorted_envp = get_sorted_list(envp);
	while (sorted_envp)
	{
		printf("declare -x %s=\"%s\"\n", sorted_envp->name, sorted_envp->value);
		sorted_envp = sorted_envp->next;
	}
	return (SUCCESS);
}

// TODO: multiple export in 1 command
// TODO: export list
// TODO: miss casten naar unsigned char ofziets!
t_status	builtin_export(t_cmd_node *nodes, t_env_var *envp)
{
	t_env_var	*new_env_var;

	if (nodes->argv[1] == NULL)
		return (list_export(envp));
	new_env_var = env_new(nodes->argv[1]);
	if (new_env_var == NULL)
		return (FAILURE);
	env_add(&envp, new_env_var);
	return (SUCCESS);
}
