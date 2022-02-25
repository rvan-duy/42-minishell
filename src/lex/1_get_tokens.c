/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1_get_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:40:27 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/25 14:41:30 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

t_token	*get_token(t_token_type type, char *str, int *i)
{
	const t_get_token	get_token_of_type[] = {
	[WHITESPACE] = &get_whitespace,
	[REDIRECT] = &get_redirect,
	[PIPE] = &get_pipe,
	[SINGLE_QUOTED] = &get_quoted,
	[DOUBLE_QUOTED] = &get_quoted,
	[UNQUOTED] = &get_unquoted
	};
	t_token				*token;
	t_error_code		err;

	token = create_token(NULL, type);
	err = get_token_of_type[type](str, i, token);
	if (err != NO_ERROR)
	{
		warn_or_error(err);
		return (NULL);
	}
	return (token);
}

t_list	*get_tokens(char *str)
{
	t_token_type	type;
	t_list			*lst;
	int				i;
	t_token			*token;

	lst = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		type = get_token_type(str[i]);
		token = get_token(type, str, &i);
		if (token == NULL)
			return (ft_lstclear(&lst, &free_token));
		ft_protect(ft_lstnew_front(token, &lst));
	}
	return (ft_lstreverse(&lst));
}
