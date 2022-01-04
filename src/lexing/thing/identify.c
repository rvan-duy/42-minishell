/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identify.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 13:49:34 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/29 12:14:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "thing.h"
#include "utilities.h"

t_bool	is_pipe(char *str)
{
	if (str[0] != '|')
		return (false);
	if (str[1] == str[0])
		return (false);
	return (true);
}

t_bool	is_redirect(char *str)
{
	if (str[0] != '<' && str[0] != '>')
		return (false);
	if (str[1] == str[0])
		return (false);
	return (true);
}

t_bool	is_double_redirect(char *str)
{
	if (str[0] != '<' && str[0] != '>')
		return (false);
	if (str[1] != str[0])
		return (false);
	if (str[2] == str[0])
		return (false);
	return (true);
}

t_bool	is_single_quoted(char *str)
{
	return (str[0] == '\'');
}

t_bool	is_double_quoted(char *str)
{
	return (str[0] == '"');
}

t_bool	is_variable(char *str)
{
	if (str[0] != '$')
		return (false);
	if (str[1] != '_' && str[1] != '?' && !ft_isalpha(str[1]))
		return (false);
	return (true);
}

t_bool	is_literal(char *str)
{
	return (str[0] != '|' && str[0] != '<' && str[0] != '>'
		&& str[0] != '\'' && str[0] != '"');
}

t_bool	is_end_of_string(char *str)
{
	return (str[0] == '\0' || ms_issep(str[0]));
}
