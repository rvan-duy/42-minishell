/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_to_arr.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 14:20:38 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 14:25:37 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "envp.h"
#include "libft.h"
#include <stdlib.h>

char	**env_list_to_arr(t_env_var *envp)
{
	const size_t	len = env_list_len(envp);
	size_t			i;
	char			**arr;

	arr = malloc(sizeof(char *) * len + 1);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = ft_strjoin_three(envp->name, "=", envp->value);
		if (arr[i] == NULL)
			return (ft_free_arr_n((void ***)&arr, i - 1));
		i++;
		envp = envp->next;
	}
	arr[i] = NULL;
	return (arr);
}
