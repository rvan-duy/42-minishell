/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_arr_to_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:04:11 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 14:26:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"

t_env_var	*env_arr_to_list(char **envp)
{
	const size_t	envp_len = ft_array_len((void **)envp);
	t_env_var		*new_envp;
	size_t			i;

	i = 0;
	new_envp = NULL;
	while (i < envp_len)
	{
		env_node_add(&new_envp, env_node_new(envp[i]));
		i++;
	}
	return (new_envp);
}
