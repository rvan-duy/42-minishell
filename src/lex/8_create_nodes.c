/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   8_create_nodes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:52:55 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/15 14:55:10 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "structs.h"
#include <stdlib.h>

t_file	*extract_redirect(t_list **tokens)
{
	t_file			*file;
	t_token_type	type;
	t_list			*next;

	file = ft_protect(malloc(sizeof(t_file)));
	file->file_name = ((t_token *)(*tokens)->next->content)->value;
	((t_token *)(*tokens)->next->content)->value = NULL;
	type = ((t_token *)(*tokens)->content)->type;
	if (is_type(type, LESS))
		file->e_type = REDIRECT_INPUT;
	else if (is_type(type, GREAT))
		file->e_type = REDIRECT_OUTPUT;
	else if (is_type(type, DLESS))
		file->e_type = HERE_DOCUMENT;
	else if (is_type(type, DGREAT))
		file->e_type = APPENDING_REDIRECT_OUTPUT;
	next = (*tokens)->next->next;
	ft_lstdelone((*tokens)->next, &free_token);
	ft_lstdelone(*tokens, &free_token);
	*tokens = next;
	return (file);
}

t_list	*extract_redirects(t_list **tokens)
{
	t_list	*files;

	files = NULL;
	while (*tokens != NULL
		&& !is_type(((t_token *)(*tokens)->content)->type, PIPE))
	{
		if (is_type(((t_token *)(*tokens)->content)->type, REDIRECT))
			ft_protect(ft_lstnew_front(extract_redirect(tokens), &files));
		else
			tokens = &(*tokens)->next;
	}
	return (ft_lstreverse(&files));
}

char	**create_argv(t_list *tokens)
{
	size_t	i;
	char	**argv;
	t_list	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp != NULL && !is_type(((t_token *)tmp->content)->type, PIPE))
	{
		tmp = tmp->next;
		i++;
	}
	argv = ft_protect(malloc((i + 1) * sizeof(char *)));
	argv[i] = NULL;
	i = 0;
	while (tokens != NULL && !is_type(((t_token *)tokens->content)->type, PIPE))
	{
		argv[i] = ((t_token *)tokens->content)->value;
		((t_token *)tokens->content)->value = NULL;
		tokens = tokens->next;
		i++;
	}
	return (argv);
}

void	create_nodes(t_list **tokens, t_cmd_node **node)
{
	while (*tokens != NULL)
	{
		*node = ft_protect(malloc(sizeof(t_cmd_node)));
		(*node)->files = extract_redirects(tokens);
		(*node)->argv = create_argv(*tokens);
		(*node)->cmd = (*node)->argv[0];
		(*node)->pipe_to = NULL;
		node = &(*node)->pipe_to;
		while (*tokens != NULL
			&& !is_type(((t_token *)(*tokens)->content)->type, PIPE))
			tokens = &(*tokens)->next;
		if (*tokens != NULL)
			tokens = &(*tokens)->next;
	}
}
