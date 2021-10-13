/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 13:06:41 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/13 16:30:51 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdlib.h>

t_status	get_env_var(char *var, char *envp[], char **dst)
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
			*dst = (envp[i] + len);
			return (SUCCESS);
		}
		i++;
	}
	free(var_equals_sign);
	*dst = NULL;
	return (SUCCESS);
}

t_bool	ms_issep(char c)
{
	return (c == ' ' || c == '\t');
}

t_bool	ms_isquote(char c)
{
	return (c == '\'' || c == '"');
}
