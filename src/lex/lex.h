/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:32:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/25 14:46:07 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "structs.h"
# include "libft.h"
# include <stdbool.h>

// -----------------------------------------------------------------------------

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
}	t_token_type;

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

typedef enum e_heredoc_state
{
	NOT_HEREDOC,
	WILL_HEREDOC,
	IN_HEREDOC
}	t_heredoc_state;

typedef t_error_code	(*t_get_token)(char *str, int *i, t_token *token);

// -----------------------------------------------------------------------------

bool			is_type(t_token_type value, t_token_type type);
void			free_token(void *token);
t_token_type	get_token_type(char initial);

void			warn(t_error_code err);
void			error(t_error_code err) __attribute__((noreturn));
void			warn_or_error(t_error_code err);

t_list			*get_tokens(char *str);
t_error_code	is_valid(t_list *tokens);
void			expand_vars(t_list *tokens, t_env_var *envp);
t_error_code	check_redirects(t_list	*tokens);
void			split_unquoted(t_list **tokens);
void			join_words(t_list **tokens);
void			remove_whitespace(t_list **tokens);
void			create_nodes(t_list **tokens, t_cmd_node **node);

t_error_code	get_whitespace(char *str, int *i, t_token *token);
t_error_code	get_redirect(char *str, int *i, t_token *token);
t_error_code	get_pipe(char *str, int *i, t_token *token);
t_error_code	get_quoted(char *str, int *i, t_token *token);
t_error_code	get_unquoted(char *str, int *i, t_token *token);

t_token			*create_token(char *value, t_token_type type);

// -----------------------------------------------------------------------------

#endif
