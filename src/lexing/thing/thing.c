/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thing.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 14:25:30 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/12/06 11:52:19 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "thing.h"
#include "utilities.h"
#include <stdlib.h>

t_symbol	*add_symbol(t_symbol_type type, t_list **symbols)
{
	t_symbol	*symbol;
	t_list		*new_list;

	symbol = malloc(sizeof(t_symbol));
	if (symbol == NULL)
		return (NULL);
	new_list = ft_lstnew_front(symbol, symbols);
	if (new_list == NULL)
	{
		free(symbol);
		return (NULL);
	}
	symbol->type = type;
	return (symbol);
}

t_symbol_type	get_symbol_type(char *str)
{
	if (is_end_of_string(str))
		return (END_OF_STRING);
	if (is_double_redirect(str))
		return (STRUCT_DOUBLE_REDIRECT);
	if (is_pipe(str))
		return (STRUCT_PIPE);
	if (is_redirect(str))
		return (STRUCT_REDIRECT);
	if (is_single_quoted(str))
		return (STRUCT_SINGLE_QUOTED);
	if (is_double_quoted(str))
		return (STRUCT_DOUBLE_QUOTED);
	if (is_variable(str))
		return (STRUCT_VARIABLE);
	return (STRUCT_LITERAL);
}

t_finish_symbol	*get_finish_table(void)
{
	static t_finish_symbol	table[7] = {
	[STRUCT_PIPE] = finish_pipe,
	[STRUCT_REDIRECT] = finish_redirect,
	[STRUCT_DOUBLE_REDIRECT] = finish_double_redirect,
	[STRUCT_VARIABLE] = finish_variable,
	[STRUCT_DOUBLE_QUOTED] = finish_double_quoted,
	[STRUCT_SINGLE_QUOTED] = finish_single_quoted,
	[STRUCT_LITERAL] = finish_literal
	};

	return (table);
}

/**
 *
 * @param[in] str Start of an argument (may have other arguments after)
 * @param[out] next_part Will be set to next argument in str
 * ("\\0" if none exist)
 * @return list of (t_symbol *)'s
 * @todo TODO: protect each symbol->value (by looping through list afterwards)
 */
t_list	*thing(char *str, char **next_part)
{
	t_list					*symbols;
	t_symbol_type			type;
	const t_finish_symbol	*finish = get_finish_table();

	symbols = NULL;
	type = get_symbol_type(str);
	while (type != END_OF_STRING)
	{
		finish[type](&str, &symbols);
		if (type == STRUCT_PIPE)
			break ;
		type = get_symbol_type(str);
		if (type == STRUCT_PIPE)
			break ;
	}
	while (ms_issep(str[0]))
		str++;
	if (next_part)
		*next_part = str;
	ft_lstreverse(&symbols);
	return (symbols);
}

void	fix_single(t_list **arg_symbol, t_list **files)
{
	const t_fix_symbol	*fix = get_fix_table();
	t_symbol			*symbol;

	if (*arg_symbol == NULL)
		return ;
	symbol = (*arg_symbol)->content;
	while (symbol->type != STRUCT_LITERAL && symbol->type != END_OF_STRING)
	{
		fix[symbol->type](arg_symbol, files);
		if (*arg_symbol == NULL)
			return ;
		symbol = (*arg_symbol)->content;
	}
}

t_bool	can_be_literalized(t_list *arg_symbol)
{
	t_symbol	*symbol;

	symbol = arg_symbol->content;
	if (symbol->type == STRUCT_LITERAL
		|| symbol->type == STRUCT_VARIABLE
		|| symbol->type == STRUCT_SINGLE_QUOTED
		|| symbol->type == STRUCT_DOUBLE_QUOTED)
		return (true);
	return (false);
}

t_fix_symbol	*get_fix_table(void)
{
	static t_fix_symbol	table[7] = {
	[STRUCT_PIPE] = fix_pipe,
	[STRUCT_REDIRECT] = fix_redirect,
	[STRUCT_DOUBLE_REDIRECT] = fix_double_redirect,
	[STRUCT_VARIABLE] = fix_variable,
	[STRUCT_DOUBLE_QUOTED] = fix_double_quoted,
	[STRUCT_SINGLE_QUOTED] = fix_single_quoted,
	[STRUCT_LITERAL] = fix_literal
	};

	return (table);
}

void	fix_thing(t_list **arg_symbols, t_list **files)
{
	const t_fix_symbol	*fix = get_fix_table();
	t_symbol			*symbol;

	while ((*arg_symbols) != NULL)
	{
		symbol = (*arg_symbols)->content;
		fix[symbol->type](arg_symbols, files);
		if (*arg_symbols == NULL)
			break ;
		symbol = (*arg_symbols)->content;
		if (symbol->type == STRUCT_LITERAL || symbol->type == STRUCT_PIPE)
			arg_symbols = &(*arg_symbols)->next;
	}
}
