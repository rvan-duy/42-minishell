/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2_validity.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:45:16 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/25 14:23:23 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdbool.h>

bool	is_valid_redirect(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL
		&& is_type(((t_token *)tokens->content)->type, WHITESPACE))
		tokens = tokens->next;
	if (tokens == NULL)
		return (false);
	if (is_type(((t_token *)tokens->content)->type, WORD))
		return (true);
	return (false);
}

bool	is_valid_pipe(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL
		&& !is_type(((t_token *)tokens->content)->type, WORD)
		&& !is_type(((t_token *)tokens->content)->type, PIPE))
		tokens = tokens->next;
	if (tokens == NULL)
		return (false);
	if (is_type(((t_token *)tokens->content)->type, WORD))
		return (true);
	return (false);
}

t_error_code	is_valid(t_list *tokens) // TODO: Better errors
{
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, REDIRECT)
			&& !is_valid_redirect(tokens))
			return (INVALID_SEQUENCE);
		else if (is_type(((t_token *)tokens->content)->type, PIPE)
			&& !is_valid_pipe(tokens))
			return (INVALID_SEQUENCE);
		tokens = tokens->next;
	}
	return (NO_ERROR);
}
