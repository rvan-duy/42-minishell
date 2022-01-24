/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iwannadie.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:48:51 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/24 18:02:50 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

typedef struct s_redirect
{
	char	*value;
	enum {
		IN,
		OUT,
		APPEND,
		HEREDOC
	} e_type;
}	t_redirect;

typedef struct s_token
{
	char	*value;
	enum {
		WORD,
		OPERATOR
	} e_type;
}	t_token;

typedef struct s_command
{
	char	**argv;
	int		argc; // ?
	t_list	*redirects; // t_redirect *
}	t_command;

/**
 * IS_DONE:
 */
void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

/**
 * IS_DONE:
 */
void	free_redirect(t_redirect *redirect)
{
	free(redirect->value);
	free(redirect);
}

/**
 * IS_DONE:
 */
void	free_command(t_command *command)
{
	ft_lstclear(&command->redirects, &free_redirect);
	ft_free_arr_dim(command->argv, 2);
	free(command);
}

/**
 * IS_DONE:
 *
 * @param tokens should be in reverse order
 */
void	tokens_to_array(t_list *tokens, t_command *command)
{
	size_t	size;

	size = ft_lstsize(tokens);
	command->argc = (int)size;
	command->argv = malloc((size + 1) * sizeof(char *));
	if (command->argv == NULL)
		return ;
	command->argv[size] = NULL;
	while (size > 0)
	{
		size--;
		command->argv[size] = ((t_token *)tokens->content)->value;
		tokens = tokens->next;
	}
}

/**
 * IS_DONE:
 */
t_list	*filter_redirects(t_list **tokens)
{
	t_list	*redirects;
	t_token	*token;
	t_list	*next;

	redirects = NULL;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->e_type == OPERATOR)
		{
			next = (*tokens)->next;
			ft_lstadd_front(&redirects, *tokens);
			*tokens = next;
		}
		else
			tokens = &(*tokens)->next;
	}
	return (redirects);
}

/**
 * // TODO: get_tokens
 */
t_list	*get_tokens(char *str)
{
	return (NULL);
}

/**
 * IS_DONE:
 */
t_command	*get_command(char *str)
{
	t_command	*command;
	t_list		*tokens;

	tokens = get_tokens(str); // is in reverse order
	if (tokens == NULL)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->redirects = filter_redirects(&tokens);
	tokens_to_array(tokens, command);
	if (command->argv == NULL)
	{
		ft_lstclear(&tokens, &free_token);
		free_command(command);
		return (NULL);
	}
	ft_lstclear(&tokens, NULL);
	return (command);
}

/**
 * IS_DONE:
 *
 * @returns list of `t_command`s
 */
t_list	*iwannadie(char *line)
{
	t_list		*commands;
	t_command	*command;
	char		**command_strings;
	size_t		i;

	commands = NULL;
	command_strings = ft_split(line, '|');
	i = 0;
	while (command_strings[i] != NULL)
	{
		command = get_command(command_strings[i]);
		if (command == NULL)
		{
			ft_lstclear(&commands, &free_command);
			ft_free_arr_dim(command_strings, 2);
			return (NULL);
		}
		ft_lstnew_front(command, &commands);
		free(command_strings[i]);
		i++;
	}
	ft_free_arr_dim(command_strings, 2);
	return (commands);
}
