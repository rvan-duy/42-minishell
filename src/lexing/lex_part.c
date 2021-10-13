/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_part.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 13:55:48 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/13 14:19:47 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utilities.h"
#include "lex.h"
#include "libft.h"

int	lex_single(char *str, t_arg ***arg)
{
	int	i;

	i = 0;
	while (str[i] != '\'')
		i++;
	set_arg(LITERAL, ft_substr(str, 0, i), *arg);
	*arg = &(**arg)->next_part;
	return (i + 1);
}

// [a-zA-Z_][a-zA-Z0-9_]*   |   ?   |   [0-9]
int	lex_var(char *str, t_arg ***arg)
{
	int	i;

	if (str[0] == '?' || ft_isdigit(str[0]))
	{
		set_arg(VARIABLE, ft_substr(str, 0, 1), *arg);
		return (1);
	}
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 0)
		set_arg(LITERAL, "$", *arg);
	else
		set_arg(VARIABLE, ft_substr(str, 0, i), *arg);
	*arg = &(**arg)->next_part;
	return (i);
}

int	lex_double(char *str, t_arg ***arg)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$')
		{
			set_arg(LITERAL, ft_substr(str, start, i - start), *arg);
			i += lex_var(&str[i + 1], arg);
			start = i + 1;
		}
		i++;
	}
	set_arg(LITERAL, ft_substr(str, start, i - start), *arg);
	*arg = &(**arg)->next_part;
	return (i + 1);
}

int	lex_none(char *str, t_arg ***arg)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (!ms_isquote(str[i]) && str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			set_arg(LITERAL, ft_substr(str, start, i - start), *arg);
			i += lex_var(&str[i + 1], arg);
			start = i + 1;
		}
		i++;
	}
	set_arg(LITERAL, ft_substr(str, start, i - start), *arg);
	*arg = &(**arg)->next_part;
	return (i - 1);
}
