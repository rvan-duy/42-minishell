/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:07:18 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/02 11:42:07 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include <signal.h>

void	env_add(t_env_var **head, t_env_var *new)
{
	t_env_var	*tmp;

	if (new == NULL)
		kill(0, SIGSEGV);
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = env_last(*head);
	tmp->next = new;
}

t_status	envp_add_2(char ***envp, const char *var)
{
	const size_t	envp_len = ft_array_len((void **)*envp) + 1;
	char			**new_envp;

	if (var == NULL)
		kill(0, SIGSEGV);
	new_envp = ft_realloc(*envp, envp_len, envp_len + 1, sizeof(char *));
	if (new_envp == NULL)
		return (FAILURE);
	new_envp[envp_len - 1] = (char *)var;
	new_envp[envp_len] = NULL;
	*envp = new_envp;
	return (SUCCESS);
}

t_status	envp_add_3(char ***envp, const char *name, const char *value)
{
	const size_t	envp_len = ft_array_len((void **)*envp) + 1;
	const char		*new_item = ft_strjoin(name, value);
	char			**new_envp;

	if (name == NULL || value == NULL)
		kill(0, SIGSEGV);
	if (new_item == NULL)
		return (FAILURE);
	new_envp = ft_realloc(*envp, envp_len, envp_len + 1, sizeof(char *));
	if (new_envp == NULL)
		return (FAILURE);
	new_envp[envp_len - 1] = (char *)new_item;
	new_envp[envp_len] = NULL;
	*envp = new_envp;
	return (SUCCESS);
}
