/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_get_var.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:55:04 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 12:55:53 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <unistd.h>
#include <stdlib.h>

/*
	Searches var inside envp, stores result in dst
*/
t_status	envp_get_var(char *var, char *envp[], char **dst)
{
	const int	len = ft_strlen(var) + 1;
	char		*var_equals_sign;
	int			i;

	var_equals_sign = ft_strjoin(var, "=");
	if (var_equals_sign == NULL)
		return (FAILURE);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_equals_sign, envp[i], len) == 0)
		{
			free(var_equals_sign);
			*dst = envp[i] + len;
			return (SUCCESS);
		}
		i++;
	}
	free(var_equals_sign);
	*dst = NULL;
	return (SUCCESS);
}
