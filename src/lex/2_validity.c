/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2_validity.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:45:16 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/16 18:12:35 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdbool.h>

t_error_code	is_valid_redirect(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL
		&& is_type(((t_token *)tokens->content)->type, WHITESPACE))
		tokens = tokens->next;
	if (tokens == NULL)
		return (UNFINISHED_REDIRECT);
	if (is_type(((t_token *)tokens->content)->type, WORD))
		return (NO_ERROR);
	return (EXPECTED_REDIRECT_FILENAME);
}

t_error_code	is_valid_pipe(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL
		&& !is_type(((t_token *)tokens->content)->type, WORD)
		&& !is_type(((t_token *)tokens->content)->type, PIPE))
		tokens = tokens->next;
	if (tokens == NULL)
		return (EMPTY_PIPE);
	if (is_type(((t_token *)tokens->content)->type, WORD))
		return (NO_ERROR);
	return (EMPTY_PIPE);
}

t_error_code	is_valid(t_list *tokens) // TODO: Better errors
{
	t_error_code	err;

	err = NO_ERROR;
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, REDIRECT))
			err = is_valid_redirect(tokens);
		else if (is_type(((t_token *)tokens->content)->type, PIPE))
			err = is_valid_pipe(tokens);
		if (err != NO_ERROR)
			return (err);
		tokens = tokens->next;
	}
	return (NO_ERROR);
}
