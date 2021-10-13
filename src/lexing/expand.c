/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 16:23:05 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/13 16:45:53 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utilities.h"
#include "libft.h"
#include <stdlib.h>

static t_status	fix_return_var(t_arg *arg)
{
	// TODO:
	arg->type = LITERAL;
	return (SUCCESS);
}

static t_status	fix_var(t_arg *arg, char *envp[])
{
	char		*str;
	t_status	status;

	if (arg->value[0] == '?')
		return (fix_return_var(arg));
	status = get_env_var(arg->value, envp, &str);
	free(arg->value);
	arg->value = NULL;
	if (status == FAILURE)
		return (FAILURE);
	if (str == NULL)
		arg->value = ft_memdup("", 1);
	else
		arg->value = ft_strdup(str);
	if (arg->value == NULL)
		return (FAILURE);
	arg->type = LITERAL;
	return (SUCCESS);
}

static t_status	fix_vars(t_arg *arg, char *envp[])
{
	while (arg != NULL)
	{
		if (arg->type == VARIABLE)
		{
			if (fix_var(arg, envp) == FAILURE)
				return (FAILURE);
		}
		arg = arg->next_part;
	}
	return (SUCCESS);
}

static size_t	arg_len(t_arg *arg)
{
	size_t	len;

	len = 0;
	while (arg != NULL)
	{
		len += ft_strlen(arg->value);
		arg = arg->next_part;
	}
	return (len);
}

t_status	expand(t_arg *arg, char *envp[], char **dst)
{
	size_t	len;
	size_t	i;

	if (fix_vars(arg, envp) == FAILURE)
		return (FAILURE);
	*dst = malloc(arg_len(arg) * sizeof(char));
	if (*dst == NULL)
		return (FAILURE);
	i = 0;
	while (arg != NULL)
	{
		len = ft_strlen(arg->value);
		ft_memcpy(&(*dst)[i], arg->value, len);
		i += len;
		arg = arg->next_part;
	}
	(*dst)[i] = '\0';
	return (SUCCESS);
}
