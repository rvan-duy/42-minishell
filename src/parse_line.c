/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 15:14:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 12:00:13 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex/lex.h"
#include "structs.h"
#include "libft.h"

t_cmd_node	*parse_line(char *line, t_env_var *envp)
{
	t_list		*tokens;
	t_cmd_node	*node;

	node = NULL;
	tokens = get_tokens(line);
	if (!is_valid(tokens))
		error(INVALID_SEQUENCE);
	expand_vars(tokens, envp);
	check_redirects(tokens);
	split_unquoted(&tokens);
	join_words(&tokens);
	remove_whitespace(&tokens);
	create_nodes(&tokens, &node);
	ft_lstclear(&tokens, &free_token);
	return (node);
}
