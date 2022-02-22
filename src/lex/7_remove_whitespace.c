/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   7_remove_whitespace.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:52:04 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 11:25:11 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void	remove_whitespace(t_list **tokens)
{
	t_list	*next;

	while (*tokens != NULL)
	{
		if (is_type(((t_token *)(*tokens)->content)->type, WHITESPACE))
		{
			next = (*tokens)->next;
			ft_lstdelone(*tokens, free_token);
			*tokens = next;
		}
		else
			tokens = &(*tokens)->next;
	}
}
