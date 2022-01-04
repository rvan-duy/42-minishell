/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finish.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 13:50:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/04 11:21:07 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "thing.h"
#include "utilities.h"

t_status	finish_pipe(char **str, t_list **symbols)
{
	t_symbol	*symbol;

	symbol = add_symbol(STRUCT_PIPE, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	symbol->value = ft_substr(*str, 0, 1);
	*str += 1;
	return (SUCCESS);
}

t_status	finish_redirect(char **str, t_list **symbols)
{
	t_symbol	*symbol;

	symbol = add_symbol(STRUCT_REDIRECT, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	symbol->value = ft_substr(*str, 0, 1);
	(*str)++;
	while (ms_issep((*str)[0]))
		(*str)++;
	return (SUCCESS);
}

t_status	finish_double_redirect(char **str, t_list **symbols)
{
	t_symbol	*symbol;

	symbol = add_symbol(STRUCT_DOUBLE_REDIRECT, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	symbol->value = ft_substr(*str, 0, 2);
	*str += 2;
	while (ms_issep((*str)[0]))
		(*str)++;
	return (SUCCESS);
}

t_status	finish_double_quoted(char **str, t_list **symbols)
{
	t_symbol	*symbol;
	char		*quote;

	quote = ft_strchr(*str + 1, '"');
	if (quote == NULL)
		return (FAILURE);
	symbol = add_symbol(STRUCT_DOUBLE_QUOTED, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	symbol->value = ft_substr(*str, 1, quote - *str - 1);
	*str = quote + 1;
	return (SUCCESS);
}

t_status	finish_single_quoted(char **str, t_list **symbols)
{
	t_symbol	*symbol;
	char		*quote;

	quote = ft_strchr(*str + 1, '\'');
	if (quote == NULL)
		return (FAILURE);
	symbol = add_symbol(STRUCT_SINGLE_QUOTED, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	symbol->value = ft_substr(*str, 1, quote - *str - 1);
	*str = quote + 1;
	return (SUCCESS);
}

t_status	finish_variable(char **str, t_list **symbols)
{
	t_symbol	*symbol;
	size_t		i;

	symbol = add_symbol(STRUCT_VARIABLE, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	if ((*str)[1] == '?')
	{
		symbol->value = ft_substr(*str, 1, 1);
		*str += 2;
		return (SUCCESS);
	}
	i = 1;
	while ((*str)[i] == '_' || ft_isalnum((*str)[i]))
		i++;
	symbol->value = ft_substr(*str, 1, i - 1);
	*str += i;
	return (SUCCESS);
}

t_status	finish_literal(char **str, t_list **symbols)
{
	t_symbol		*symbol;
	t_symbol_type	type;
	size_t			i;

	symbol = add_symbol(STRUCT_LITERAL, symbols);
	if (symbol == NULL)
	{
		// free symbols
		ft_putendl_fd("hello", 1);
		return (FAILURE);
	}
	i = 0;
	type = get_symbol_type(*str + i);
	while (type == STRUCT_LITERAL)
	{
		type = get_symbol_type(*str + i);
		i++;
	}
	symbol->value = ft_substr(*str, 0, i - 1);
	*str += i - 1;
	return (SUCCESS);
}
