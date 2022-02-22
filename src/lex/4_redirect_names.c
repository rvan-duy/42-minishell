/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   4_redirect_names.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:48:24 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 11:24:17 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

bool	is_valid_redirect_name(t_list *tokens)
{
	while (tokens != NULL && !is_type(((t_token *)tokens->content)->type, WORD))
		tokens = tokens->next;
	while (tokens != NULL && is_type(((t_token *)tokens->content)->type, WORD))
	{
		if (is_type(((t_token *)tokens->content)->type, UNQUOTED) \
		&& (ft_strchr(((t_token *)tokens->content)->value, ' ') != NULL \
		|| ft_strchr(((t_token *)tokens->content)->value, '\t') != NULL))
			return (false);
		tokens = tokens->next;
	}
	return (true);
}

void	check_redirects(t_list	*tokens)
{
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, REDIRECT)
			&& !is_type(((t_token *)tokens->content)->type, DGREAT)
			&& !is_valid_redirect_name(tokens))
			error(AMBIGUOUS_REDIRECT);
		tokens = tokens->next;
	}
}
