/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fix.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 13:51:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/04 12:27:51 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "thing.h"
#include <stdlib.h>

static void	fix_double_quoted_aux(t_list **new, char **str, char **start)
{
	t_symbol		*symbol;
	t_symbol_type	type;

	type = get_symbol_type(*str);
	if (type == STRUCT_VARIABLE)
	{
		add_symbol(STRUCT_LITERAL, new);
		symbol = (*new)->content;
		symbol->value = ft_substr(*start, 0, (*str) - (*start));
		finish_variable(str, new);
		*start = *str;
	}
	else
		(*str)++;
}

void	fix_double_quoted(t_list **arg_symbols, t_list **files)
{
	t_list			*new;
	char			*start;
	char			*str;

	(void)files;
	str = ((t_symbol *)(*arg_symbols)->content)->value;
	new = NULL;
	start = str;
	while (str[0] != '\0')
	{
		fix_double_quoted_aux(&new, &str, &start);
	}
	add_symbol(STRUCT_LITERAL, &new);
	((t_symbol *)new->content)->value = ft_substr(start, 0, str - start);
	ft_lstreverse(&new);
	ft_lstadd_back(&new, (*arg_symbols)->next);
	ft_lstdelone(*arg_symbols, NULL); // TODO: use actual del function
	*arg_symbols = new;
}

void	fix_single_quoted(t_list **arg_symbols, t_list **files)
{
	(void)files;
	((t_symbol *)(*arg_symbols)->content)->type = STRUCT_LITERAL;
	(void)arg_symbols;
}

void	fix_pipe(t_list **arg_symbols, t_list **files)
{
	(void)files;
	(void)arg_symbols;
	// ((t_symbol *)(*arg_symbols)->content)->type = STRUCT_LITERAL;
}

void	del_symbol(void *symbol)
{
	free(((t_symbol *)symbol)->value);
	free(symbol);
}

void	fix_redirect(t_list **arg_symbols, t_list **files)
{
	t_symbol	*symbol;
	t_symbol	*next_symbol;
	t_files		*file;
	t_list		*tmp;

	symbol = (*arg_symbols)->content;
	if (!can_be_literalized((*arg_symbols)->next))
	{
		// FIXME: Error unexpected token (next)
	}
	fix_single(&(*arg_symbols)->next, files);
	next_symbol = (*arg_symbols)->next->content;
	file = malloc(sizeof(t_files));
	file->file_name = ft_strdup(next_symbol->value);
	if (symbol->value[0] == '<')
		file->e_type = IN;
	else
		file->e_type = OUT;
	ft_lstnew_front(file, files);
	tmp = (*arg_symbols)->next->next;
	ft_lstdelone((*arg_symbols)->next, del_symbol);
	ft_lstdelone(*arg_symbols, del_symbol);
	*arg_symbols = tmp;
}

void	fix_double_redirect(t_list **arg_symbols, t_list **files)
{
	t_symbol	*symbol;
	t_symbol	*next_symbol;
	t_files		*file;
	t_list		*tmp;

	symbol = (*arg_symbols)->content;
	if (!can_be_literalized((*arg_symbols)->next))
	{
		// FIXME: Error unexpected token (next)
	}
	fix_single(&(*arg_symbols)->next, files);
	next_symbol = (*arg_symbols)->next->content;
	file = malloc(sizeof(t_files));
	file->file_name = ft_strdup(next_symbol->value);
	if (symbol->value[0] == '<')
		file->e_type = HEREDOC_IN;
	else
		file->e_type = HEREDOC_OUT;
	ft_lstnew_front(file, files);
	tmp = (*arg_symbols)->next->next;
	ft_lstdelone((*arg_symbols)->next, del_symbol);
	ft_lstdelone(*arg_symbols, del_symbol);
	*arg_symbols = tmp;
}

void	fix_variable(t_list **arg_symbols, t_list **files)
{
	(void)files;
	(void)arg_symbols;
	((t_symbol *)(*arg_symbols)->content)->type = STRUCT_LITERAL;
}

void	fix_literal(t_list **arg_symbols, t_list **files)
{
	(void)files;
	(void)arg_symbols;
}
