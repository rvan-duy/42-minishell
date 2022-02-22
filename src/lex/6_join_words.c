/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   6_join_words.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:51:30 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 11:25:05 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

void	join_words_token(t_list **tokens)
{
	char	*out_str;
	char	*tmp;
	t_list	*next;

	out_str = ft_protect(ft_strdup(""));
	while (*tokens != NULL
		&& is_type(((t_token *)(*tokens)->content)->type, WORD))
	{
		tmp = ft_protect(\
			ft_strjoin(out_str, ((t_token *)(*tokens)->content)->value));
		free(out_str);
		out_str = tmp;
		next = (*tokens)->next;
		ft_lstdelone(*tokens, &free_token);
		*tokens = next;
	}
	ft_protect(ft_lstnew_front(\
		ft_protect(create_token(out_str, WORD)), tokens));
}

void	join_words(t_list **tokens)
{
	while (*tokens != NULL)
	{
		if (is_type(((t_token *)(*tokens)->content)->type, WORD))
		{
			join_words_token(tokens);
		}
		tokens = &(*tokens)->next;
	}
}
