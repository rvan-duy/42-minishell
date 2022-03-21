/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   4_redirect_names.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:48:24 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/21 16:56:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

bool	is_valid_redirect_name(t_list *tokens)
{
	bool	all_null;

	while (tokens != NULL && !is_type(((t_token *)tokens->content)->type, WORD))
		tokens = tokens->next;
	all_null = true;
	while (tokens != NULL && is_type(((t_token *)tokens->content)->type, WORD))
	{
		if (is_type(((t_token *)tokens->content)->type, UNQUOTED) \
		&& ((t_token *)tokens->content)->value[0] == '\0')
		{
			tokens = tokens->next;
			continue ;
		}
		all_null = false;
		if (is_type(((t_token *)tokens->content)->type, UNQUOTED) \
		&& (ft_strchr(((t_token *)tokens->content)->value, ' ') != NULL \
		|| ft_strchr(((t_token *)tokens->content)->value, '\t') != NULL))
			return (false);
		tokens = tokens->next;
	}
	if (all_null)
		return (false);
	return (true);
}

t_error_code	check_redirects(t_list	*tokens)
{
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, REDIRECT)
			&& !is_type(((t_token *)tokens->content)->type, DGREAT)
			&& !is_valid_redirect_name(tokens))
			return (AMBIGUOUS_REDIRECT);
		tokens = tokens->next;
	}
	return (NO_ERROR);
}
