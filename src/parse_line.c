/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 15:14:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/04/06 12:30:08 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "structs.h"
#include "libft.h"

t_cmd_node	*parse_line(char *line, t_env_var *envp)
{
	t_list			*tokens;
	t_cmd_node		*node;
	t_error_code	error_code;

	node = NULL;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);
	error_code = is_valid(tokens);
	if (error_code == NO_ERROR)
	{
		expand_vars(tokens, envp);
		error_code = check_redirects(tokens);
	}
	if (error_code != NO_ERROR)
	{
		warn_or_error(error_code);
		return (ft_lstclear(&tokens, &free_token));
	}
	fix_unquoted(&tokens);
	join_words(&tokens);
	remove_whitespace(&tokens);
	create_nodes(&tokens, &node);
	ft_lstclear(&tokens, &free_token);
	return (node);
}
