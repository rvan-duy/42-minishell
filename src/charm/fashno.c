/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fashno.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:29:27 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/14 16:48:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum e_token_type
{
	WHITESPACE = 1 << 0,
	OPERATOR = 1 << 1,
		PIPE = OPERATOR | 1 << 2,
		REDIRECT = OPERATOR | 1 << 3,
			LESS = REDIRECT | 1 << 4,
			GREAT = REDIRECT | 1 << 5,
			DLESS = REDIRECT | 1 << 6,
			DGREAT = REDIRECT | 1 << 7,
	WORD = 1 << 8,
		UNQUOTED = WORD | 1 << 9,
		QUOTED = WORD | 1 << 10,
			SINGLE_QUOTED = QUOTED | 1 << 11,
			DOUBLE_QUOTED = QUOTED | 1 << 12
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

typedef enum e_error_code
{
	NO_ERROR = 0,
	MALLOC_FAIL,
	MISSING_SINGLE_QUOTE,
	MISSING_DOUBLE_QUOTE,
	AMBIGUOUS_REDIRECT,
	INVALID_SEQUENCE
}	t_error_code;

typedef t_error_code	(*t_get_token)(char *str, int *i, t_token *token);

bool	is_type(t_token_type value, t_token_type type)
{
	return ((value & type) == type);
}

t_token_type	get_token_type(char initial)
{
	static const t_token_type	type[] = {\
		[' '] = WHITESPACE, \
		['\t'] = WHITESPACE, \
		['<'] = REDIRECT, \
		['>'] = REDIRECT, \
		['|'] = PIPE, \
		['\''] = SINGLE_QUOTED, \
		['\"'] = DOUBLE_QUOTED \
	};

	if (ft_strchr(" \t<>|\'\"", initial) != NULL)
		return (type[initial]);
	return (UNQUOTED);
}

void	error(t_error_code err) __attribute__((noreturn));

void	error(t_error_code err)
{
	static char	*err_str[] = {\
		[MALLOC_FAIL] = "Malloc failed", \
		[MISSING_SINGLE_QUOTE] = "Unexpected EOL while looking for matching (\')", \
		[MISSING_DOUBLE_QUOTE] = "Unexpected EOL while looking for matching (\")", \
		[AMBIGUOUS_REDIRECT] = "Ambiguous redirect", \
		[INVALID_SEQUENCE] = "Invalid sequence" \
	};

	ft_putendl_fd(err_str[err], STDERR_FILENO);
	exit(err);
}

t_error_code	get_whitespace(char *str, int *i, t_token *token)
{
	const int	start = *i;

	while (str[*i] != '\0' && ft_strchr(" \t", str[*i]) != NULL)
		(*i)++;
	token->value = ft_substr(str, start, *i - start); // ± 1
	if (token->value == NULL)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

t_error_code	get_redirect(char *str, int *i, t_token *token)
{
	const int	start = *i;

	if (str[*i + 1] == str[*i])
		(*i)++;
	token->value = ft_substr(str, start, *i - start + 1); // ± 1
	if (token->value == NULL)
		return (MALLOC_FAIL);
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
	token->value = ft_substr(str, *i, 1);
	if (token->value == NULL)
		return (MALLOC_FAIL);
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
	token->value = ft_substr(str, start + 1, *i - start - 1);
	if (token->value == NULL)
		return (MALLOC_FAIL);
	(*i)++;
	return (NO_ERROR);
}

t_error_code	get_unquoted(char *str, int *i, t_token *token)
{
	const int	start = *i;

	while (get_token_type(str[*i]) == UNQUOTED && str[*i] != '\0')
		(*i)++;
	token->value = ft_substr(str, start, *i - start);
	if (token->value == NULL)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		error(MALLOC_FAIL);
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*get_token(t_token_type type, char *str, int *i)
{
	const t_get_token	get_token_of_type[] = {\
		[WHITESPACE] = get_whitespace, \
		[REDIRECT] = get_redirect, \
		[PIPE] = get_pipe, \
		[SINGLE_QUOTED] = get_quoted, \
		[DOUBLE_QUOTED] = get_quoted, \
		[UNQUOTED] = get_unquoted \
	};
	t_token				*token;
	t_error_code		err;

	token = create_token(NULL, type);
	err = get_token_of_type[type](str, i, token);
	if (err)
		error(err);
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
		if (ft_lstnew_front(token, &lst) == NULL)
			error(MALLOC_FAIL);
	}
	return (ft_lstreverse(&lst));
}

bool	is_valid_redirect(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL
		&& is_type(((t_token *)tokens->content)->type, WHITESPACE))
		tokens = tokens->next;
	if (tokens == NULL)
		return (false);
	if (is_type(((t_token *)tokens->content)->type, WORD))
		return (true);
	return (false);
}

bool	is_valid_pipe(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL
		&& !is_type(((t_token *)tokens->content)->type, WORD)
		&& !is_type(((t_token *)tokens->content)->type, PIPE))
		tokens = tokens->next;
	if (tokens == NULL)
		return (false);
	if (is_type(((t_token *)tokens->content)->type, WORD))
		return (true);
	return (false);
}

bool	is_valid(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, REDIRECT)
			&& !is_valid_redirect(tokens))
			return (false);
		else if (is_type(((t_token *)tokens->content)->type, PIPE)
			&& !is_valid_pipe(tokens))
			return (false);
		tokens = tokens->next;
	}
	return (true);
}

char	*lookup_var(char *var_name)
{
	if (var_name == NULL)
		return (NULL);
	return (ft_strjoin(ft_strjoin("THIS_IS_A_ VAR=>", var_name), "<"));
}

char	*get_var_value(char *str, int *var_name_start)
{
	const int	start = *var_name_start + 1;

	(*var_name_start)++;
	while (str[*var_name_start] != '\0'
		&& (ft_isalnum(str[*var_name_start]) || str[*var_name_start] == '_'))
		(*var_name_start)++;
	if (start == *var_name_start)
		return (ft_strdup("$"));
	return (lookup_var(ft_substr(str, start, *var_name_start - start)));
}

t_list	*get_replace_vars_parts(char *str) // TODO: many malloc protections needed
{
	t_list	*lst;
	int		i;
	int		start;

	lst = NULL;
	start = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			ft_lstnew_front(ft_substr(str, start, i - start), &lst);
			ft_lstnew_front(get_var_value(str, &i), &lst);
			start = i;
		}
		else
			i++;
	}
	ft_lstnew_front(ft_substr(str, start, i - start), &lst);
	return (ft_lstreverse(&lst));
}

char	*replace_vars(char *str)
{
	t_list	*lst;
	t_list	*copy;
	int		len;
	char	*out;

	lst = get_replace_vars_parts(str);
	copy = lst;
	len = 0;
	while (copy != NULL)
	{
		len += ft_strlen(copy->content);
		copy = copy->next;
	}
	out = ft_calloc(len + 1, sizeof(char));
	copy = lst;
	while (copy != NULL)
	{
		ft_strlcat(out, copy->content, (len + 1) * sizeof(char));
		copy = copy->next;
	}
	return (out);
}

void	expand_vars(t_list *tokens)
{
	char	*tmp;
	enum	{ NOT, WILL, IN } heredoc_state;

	heredoc_state = NOT;
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, DLESS))
			heredoc_state = WILL;
		else if ((is_type(((t_token *)tokens->content)->type, UNQUOTED)
			|| is_type(((t_token *)tokens->content)->type, DOUBLE_QUOTED))
			&& heredoc_state == NOT)
		{
			tmp = replace_vars(((t_token *)tokens->content)->value);
			free(((t_token *)tokens->content)->value);
			((t_token *)tokens->content)->value = tmp;
		}
		else if (is_type(((t_token *)tokens->content)->type, WORD)
			&& heredoc_state != NOT)
			heredoc_state = IN;
		else if (heredoc_state == IN
			&& !is_type(((t_token *)tokens->content)->type, WORD))
			heredoc_state = NOT;
		tokens = tokens->next;
	}
}

bool	is_valid_redirect_name(t_list *tokens)
{
	while (tokens != NULL && !is_type(((t_token *)tokens->content)->type, WORD))
		tokens = tokens->next;
	while (tokens != NULL && is_type(((t_token *)tokens->content)->type, WORD))
	{
		if (is_type(((t_token *)tokens->content)->type, UNQUOTED)
			&& (ft_strchr(((t_token *)tokens->content)->value, ' ') != NULL
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

void	free_token(void *_token)
{
	t_token	*token;

	token = _token;
	free(token->value);
	free(token);
}

void	split_unquoted_token(t_list **token) // do with ptr
{
	char	**splitted;
	t_list	*next;
	int		i;

	splitted = ft_split(((t_token *)(*token)->content)->value, ' ');
	i = 0;
	while (splitted[i] != NULL)
	{
		ft_lstnew_front(create_token(splitted[i], UNQUOTED), token);
		token = &(*token)->next;
		if (splitted[i + 1] != NULL)
		{
			ft_lstnew_front(create_token(NULL, WHITESPACE), token);
			token = &(*token)->next;
		}
		i++;
	}
	next = (*token)->next;
	ft_lstdelone(*token, &free_token);
	*token = next;
}

void	split_unquoted(t_list **tokens)
{
	while (*tokens != NULL)
	{
		if (is_type(((t_token *)(*tokens)->content)->type, UNQUOTED)
			&& ft_strchr(((t_token *)(*tokens)->content)->value, ' ') != NULL)
		{
			split_unquoted_token(tokens); // do with ptr
		}
		tokens = &(*tokens)->next;
	}
}

void	join_words_token(t_list **tokens)
{
	char	*out_str;
	char	*tmp;
	t_list	*next;

	out_str = ft_strdup("");
	while (*tokens != NULL
		&& is_type(((t_token *)(*tokens)->content)->type, WORD))
	{
		tmp = ft_strjoin(out_str, ((t_token *)(*tokens)->content)->value);
		free(out_str);
		out_str = tmp;
		next = (*tokens)->next;
		ft_lstdelone(*tokens, &free_token);
		*tokens = next;
	}
	ft_lstnew_front(create_token(out_str, WORD), tokens);
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

#include <stdio.h>
void	parse_line(char *line)
{
	t_list	*tokens;

	tokens = get_tokens(line);
	if (!is_valid(tokens))
		error(INVALID_SEQUENCE);
	expand_vars(tokens);
	check_redirects(tokens);
	split_unquoted(&tokens);
	join_words(&tokens);

	t_token *token;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		printf("token value: {%s}\n", token->value);
		printf("token type: %i\n\n", token->type);
		tokens = tokens->next;
	}
}

int main(void)
{
	parse_line(" echo hello      |<hello|<<hello cat $TEST << $HEYA$hoi\"s\"'r'$h $TE\"s$ $hello\" '$heyo' > \"$iuef\" ");
	return (0);
}
