/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_dup.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:04:11 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/14 16:19:59 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**envp_dup(char **envp)
{
	const size_t	envp_len = ft_array_len((void **)envp);
	char			**new_envp;
	size_t			i;

	new_envp = malloc((sizeof(char *) * envp_len) + 1);
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	while (i < envp_len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
			return (ft_free_arr((void ***)&new_envp));
		i++;
	}
	return (new_envp);
}
