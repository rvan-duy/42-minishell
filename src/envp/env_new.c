/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_new.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 14:15:38 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/02 12:50:17 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>
#include <signal.h>

// Either put this in libft or utils..
static size_t	first_occurrence(const char *env_var, const char c)
{
	size_t	i;

	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == c)
			return (i);
		i++;
	}
	return (i);
}

t_env_var	*env_new(const char *env_var)
{
	const size_t	split_index = first_occurrence(env_var, '=');
	t_env_var		*new_envp;

	if (env_var == NULL)
		kill(0, SIGSEGV);
	new_envp = malloc(sizeof(t_env_var));
	if (new_envp == NULL)
		return (NULL);
	new_envp->name = ft_strndup(env_var, split_index);
	if (new_envp->name == NULL)
		return (NULL);
	new_envp->value = ft_strdup(env_var + split_index + 1);
	if (new_envp->value == NULL)
		return (NULL);
	new_envp->next = NULL;
	return (new_envp);
}
