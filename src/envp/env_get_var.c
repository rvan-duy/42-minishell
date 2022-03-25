/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_get_var.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:55:04 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/25 10:58:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>

t_env_var	*env_get_var(const char *name, t_env_var *envp)
{
	const size_t	len = ft_strlen(name);

	while (envp != NULL)
	{
		if (ft_strncmp(name, envp->name, len + 1) != 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}
