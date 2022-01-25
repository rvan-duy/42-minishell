/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iwannadie.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 16:48:51 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/25 17:28:23 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum e_redirect_type {
	IN,
	OUT,
	APPEND,
	HEREDOC,
	UNKNOWN
}	t_redirect_type;

typedef enum e_token_type {
	WORD,
	OPERATOR,
	END
}	t_token_type;

typedef struct s_redirect
{
	char			*value;
	t_redirect_type	type;

}	t_redirect;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
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
void	free_token_no_fail(t_token *token)
{
	free(token->value);
	free(token);
}

/**
 * IS_DONE:
 */
void	free_token_keep_value_no_fail(t_token *token)
{
	free(token->value);
	free(token);
}

/**
 * IS_DONE:
 */
void	free_redirect_no_fail(t_redirect *redirect)
{
	free(redirect->value);
	free(redirect);
}

/**
 * IS_DONE:
 */
void	free_command_no_fail(t_command *command)
{
	ft_lstclear(&command->redirects, &free_redirect_no_fail);
	ft_free_arr_dim(command->argv, 2);
	free(command);
}

/**
 * IS_DONE:
 *
 * @param tokens should be in reverse order
 */
void	tokens_to_array_fail(t_list *tokens, t_command *command)
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
t_redirect_type	classify_redirect_no_fail(char *str)
{
	const static void	*thing[][2] = {\
		{"<", IN}, {">", OUT}, {">>", APPEND}, {"<<", HEREDOC}, NULL
	};
	size_t				i;

	i = 0;
	while (thing[i] != NULL)
	{
		if (ft_strcmp(str, thing[i][0]) == 0)
			return (thing[i][1]);
		i++;
	}
	return (UNKNOWN);
}

/**
 * // IS_DONE:
 */
t_redirect	*filter_redirect_fail(t_list **token_p)
{
	t_redirect	*redirect;
	t_token		*token;
	t_token		*next_token;
	t_list		*next;

	next = (*token_p)->next;
	next_token = next->content;
	if (next == NULL || next_token->type == OPERATOR)
		return (NULL);
	redirect = malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	token = (*token_p)->content;
	redirect->type = classify_redirect_no_fail(token->value);
	redirect->value = next_token->value;
	free_token_keep_value_no_fail(next);
	free_token_no_fail(*token_p);
	*token_p = next->next;
	return (redirect);
}

/**
 * IS_DONE:
 */
t_list	*filter_redirects_fail(t_list **tokens)
{
	t_list		*redirects;
	t_token		*token;
	// t_list		*next;
	t_redirect	*redir;

	redirects = NULL;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == OPERATOR)
		{
			redir = filter_redirect_fail(tokens);
			if (redir == NULL || ft_lstnew_front(redir, &redirects) == NULL)
			{
				ft_lstclear(&redirects, &free_redirect_no_fail);
				return (NULL);
			};
			// next = (*tokens)->next;
			// ft_lstadd_front(&redirects, *tokens);
			// *tokens = next;
		}
		else
			tokens = &(*tokens)->next;
	}
	return (redirects);
}

typedef char *	t_string;

/**
 * IS_DONE:
 */
const t_string	*get_operator_arr(void)
{
	const static t_string	ops[] = {"<", ">", "<<", ">>", NULL};

	return (ops);
}

/**
 * IS_DONE:
 */
size_t	get_op_len_no_fail(t_string str)
{
	const t_string	*ops = get_operator_arr();
	size_t			i;
	size_t			len;

	i = 0;
	len = 0;
	while (ops[i] != NULL)
	{
		while (ops[i][len] != '\0' && str[len] != '\0'
			&& ops[i][len] == str[len])
			len++;
		i++;
		while (ops[i] != NULL && ft_strncmp(ops[i], str, len + 1) != 0)
			i++;
	}
	return (len);
}

/**
 * IS_DONE:
 */
t_token	*get_op_fail(t_string *str_p, t_token *token)
{
	const size_t	len = get_op_len_no_fail(*str_p);

	token->type = OPERATOR;
	token->value = ft_substr(*str_p, 0, len);
	if (token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	*str_p += len;
	return (token);
}

/**
 * // TODO: get_word_fail
 */
t_token	*get_word_fail(t_string *str_p, t_token *token)
{
	while (**str_p != '\0' && !can_start_op(**str_p)
		&& **str_p != ' ' && **str_p != '\t')
	{
		if (**str_p == '\'')
			get_single_quoted(); // TODO: create function: get_single_quoted
		else if (**str_p == '"')
			get_double_quoted(); // TODO: create function: get_double_quoted
		else
			get_unquoted(); // TODO: create function: get_unquoted
	}
	return (token);
}

/**
 * IS_DONE:
 */
bool	can_start_op(char c)
{
	const t_string	*ops = get_operator_arr();
	size_t			i;

	i = 0;
	while (ops[i] != NULL)
	{
		if (ops[i][0] == c)
			return (true);
		i++;
	}
	return (false);
}

/**
 * IS_DONE:
 */
t_token	*get_next_token_fail(t_string *str_p)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	while (**str_p == ' ' || **str_p == '\t')
		(*str_p)++;
	if (**str_p == '\0')
	{
		token->type = END;
		token->value = NULL;
		return (token);
	}
	if (can_start_op(**str_p))
		return (get_op_fail(str_p, token));
	return (get_word_fail(str_p, token));
}

/**
 * //TODO: get_var(_fail?)
 */
t_string	get_var(char *dollar, t_string *str_p)
{
	return (NULL);
}

/**
 * IS_DONE:
 */
t_string	append_all_fail(t_string str1_m, t_string str2)
{
	const size_t	start_len = ft_strlen(str1_m);
	const size_t	end_len = ft_strlen(str2);
	char			*dst;

	dst = malloc((start_len + end_len + 1) * sizeof(char));
	if (dst == NULL)
	{
		free(str1_m);
		return (NULL);
	}
	ft_memcpy(dst, str1_m, start_len);
	ft_memcpy(dst + start_len, str2, end_len);
	dst[start_len + end_len] = '\0';
	free(str1_m);
	return (dst);
}

/**
 * IS_DONE:
 */
t_string	append_fail(t_string str1_m, t_string str2, size_t len)
{
	const size_t	start_len = ft_strlen(str1_m);
	char			*dst;

	dst = malloc((start_len + len + 1) * sizeof(char));
	if (dst == NULL)
	{
		free(str1_m);
		return (NULL);
	}
	ft_memcpy(dst, str1_m, start_len);
	ft_memcpy(dst + start_len, str2, len);
	dst[start_len + len] = '\0';
	free(str1_m);
	return (dst);
}

/**
 * IS_DONE:
 */
t_string	replace_vars_fail(t_string str)
{
	char		*dollar;
	t_string	dst;
	t_string	var;

	dst = NULL;
	while (*str != '\0')
	{
		dollar = ft_strchr(str, '$');
		if (dollar == NULL)
			return (append_fail(dst, str, ft_strlen(str)));
		dst = append_fail(dst, str, dollar - str);
		if (dst == NULL)
			return (NULL);
		var = get_var(dollar, &str);
		if (var == NULL)
			return (NULL);
		dst = append_all_fail(dst, var);
		if (dst == NULL)
		{
			free(var);
			return (NULL);
		}
	}
	return (dst);
}

/**
 * IS_DONE:
 */
t_list	*get_tokens_fail(t_string str)
{
	t_list	*tokens;
	t_token	*token;

	str = replace_vars_fail(str);
	if (str == NULL)
		return (NULL);
	tokens = NULL;
	while (str[0] != '\0')
	{
		token = get_next_token_fail(&str);
		if (token == NULL || ft_lstnew_front(token, &tokens) == NULL)
		{
			ft_lstclear(&tokens, &free_token_no_fail);
			return (NULL);
		}
	}
	return (tokens);
}

/**
 * IS_DONE:
 */
t_command	*get_command_fail(char *str)
{
	t_command	*command;
	t_list		*tokens;

	tokens = get_tokens_fail(str); // is in reverse order
	if (tokens == NULL)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->redirects = filter_redirects_fail(&tokens);
	// if (command->redirects == NULL)
	// {
	// 	ft_lstclear(&tokens, &free_token_no_fail);
	// 	free_command_no_fail(command);
	// 	return (NULL);
	// }
	tokens_to_array_fail(tokens, command);
	// `command->redirects == NULL` might have to be own if (above `tokens_to_array`)
	if (command->argv == NULL || command->redirects == NULL)
	{
		ft_lstclear(&tokens, &free_token_no_fail);
		free_command_no_fail(command);
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
t_list	*iwannadie_fail(char *line)
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
		command = get_command_fail(command_strings[i]);
		if (command == NULL || ft_lstnew_front(command, &commands) == NULL)
		{
			ft_lstclear(&commands, &free_command_no_fail);
			ft_free_arr_dim(command_strings, 2);
			return (NULL);
		}
		free(command_strings[i]);
		i++;
	}
	ft_free_arr_dim(command_strings, 2);
	return (commands);
}
