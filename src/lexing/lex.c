/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 12:57:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/20 11:54:32 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utilities.h"
#include "lex.h"
#include "libft.h"
#include <stdlib.h>

char	*get_arg(char *part, char **after_part)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (part[i] != '\0')
	{
		if (ms_isquote(part[i]))
		{
			if (quote == '\0')
				quote = part[i];
			else if (quote == part[i])
				quote = '\0';
		}
		else if (quote == '\0' && ms_issep(part[i]))
		{
			*after_part = part + i;
			return (ft_substr(part, 0, i));
		}
		i++;
	}
	*after_part = part + i;
	if (quote == '\0')
		return (ft_memdup(part, i + 1));
	return (NULL);
}

t_status	set_arg(t_arg_type type, char *value, t_arg **arg)
{
	if (value == NULL)
		return (FAILURE);
	// FIXME: exit on malloc fail
	*arg = malloc(sizeof(t_arg));
	if (*arg == NULL)
		return (FAILURE);
	(*arg)->type = type;
	(*arg)->value = value;
	(*arg)->next_part = NULL;
	return (SUCCESS);
}

t_arg	*lex_arg(char *str)
{
	int		i;
	t_arg	*arg;
	t_arg	**arg2;
	t_arg	***cur;

	arg = NULL;
	arg2 = &arg;
	cur = &arg2;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			i += lex_single(&str[i + 1], cur);
		else if (str[i] == '\"')
			i += lex_double(&str[i + 1], cur);
		else
			i += lex_none(&str[i], cur);
		i++;
	}
	return (arg);
}
