/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_node_new.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 14:15:38 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/11 15:04:22 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>
#include <signal.h>

static t_status	first_occurrence(const char *env_var, const char c,
	size_t *index)
{
	size_t	i;

	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == c)
		{
			*index = i;
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

t_env_var	*env_node_new(const char *env_var)
{
	t_env_var	*new_envp;
	size_t		split_index;

	if (env_var == NULL)
		kill(0, SIGSEGV);
	new_envp = ft_protect(malloc(sizeof(t_env_var)));
	if (first_occurrence(env_var, '=', &split_index) == SUCCESS)
	{
		new_envp->name = ft_protect(ft_strndup(env_var, split_index));
		new_envp->value = ft_protect(ft_strdup(env_var + split_index + 1));
	}
	else
	{
		new_envp->name = ft_protect(ft_strdup(env_var));
		new_envp->value = NULL;
	}
	new_envp->next = NULL;
	return (new_envp);
}
