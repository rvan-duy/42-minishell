/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1a_token_completion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:36:13 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 11:24:06 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_error_code	get_whitespace(char *str, int *i, t_token *token)
{
	while (str[*i] != '\0' && ft_strchr(" \t", str[*i]) != NULL)
		(*i)++;
	token->value = NULL;
	return (NO_ERROR);
}

t_error_code	get_redirect(char *str, int *i, t_token *token)
{
	const int	start = *i;

	if (str[*i + 1] == str[*i])
		(*i)++;
	if (str[start] == '>' && start == *i)
		token->type = GREAT;
	else if (str[start] == '<' && start == *i)
		token->type = LESS;
	else if (str[start] == '>')
		token->type = DGREAT;
	else if (str[start] == '<')
		token->type = DLESS;
	(*i)++;
	return (NO_ERROR);
}

t_error_code	get_pipe(char *str, int *i, t_token *token)
{
	(void)str;
	(void)token;
	(*i)++;
	return (NO_ERROR);
}

t_error_code	get_quoted(char *str, int *i, t_token *token)
{
	const int	start = *i;
	const char	quote = str[start];

	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '\0' && quote == '\'')
		return (MISSING_SINGLE_QUOTE);
	if (str[*i] == '\0' && quote == '\"')
		return (MISSING_DOUBLE_QUOTE);
	token->value = ft_protect(ft_substr(str, start + 1, *i - start - 1));
	(*i)++;
	return (NO_ERROR);
}

t_error_code	get_unquoted(char *str, int *i, t_token *token)
{
	const int	start = *i;

	while (get_token_type(str[*i]) == UNQUOTED && str[*i] != '\0')
		(*i)++;
	token->value = ft_protect(ft_substr(str, start, *i - start));
	return (NO_ERROR);
}
