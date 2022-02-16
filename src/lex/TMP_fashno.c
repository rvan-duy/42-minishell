/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fashno.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 12:29:27 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/16 15:18:06 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "libft.h"
#include "structs.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

char *token_type_as_str(int type)
{
	switch (type)
	{
		case WHITESPACE: return "WHITESPACE";
		case OPERATOR: return "OPERATOR";
		case PIPE: return "PIPE";
		case REDIRECT: return "REDIRECT";
		case LESS: return "LESS";
		case GREAT: return "GREAT";
		case DLESS: return "DLESS";
		case DGREAT: return "DGREAT";
		case WORD: return "WORD";
		case UNQUOTED: return "UNQUOTED";
		case QUOTED: return "QUOTED";
		case SINGLE_QUOTED: return "SINGLE_QUOTED";
		case DOUBLE_QUOTED: return "DOUBLE_QUOTED";
	}
	return "";
}

char *all_types(int type)
{
	static t_token_type types[] = {
		WHITESPACE,
		OPERATOR,
		PIPE,
		REDIRECT,
		LESS,
		GREAT,
		DLESS,
		DGREAT,
		WORD,
		UNQUOTED,
		QUOTED,
		SINGLE_QUOTED,
		DOUBLE_QUOTED
	};
	char *type_str = ft_strdup("");
	for (size_t i = 0; i < sizeof(types) / sizeof(t_token_type); i++)
	{
		if (is_type(type, types[i]))
		{
			if (type_str[0] != '\0')
				type_str = ft_strjoin(type_str, ", ");
			type_str = ft_strjoin(type_str, token_type_as_str(types[i]));
		}
	}
	return (type_str);
}

int	main(void)
{
	parse_line(" echo < q hello      |<hello|<<hello cat $TEST << $HEYA$hoi\"s\"'r'$h $TE\"s$ $hello\" '$heyo' > \"$iuef\" ");

	// t_token *token;
	// size_t	i = 0;
	// printf("-----------------------------------------------------------------------------------------------------\n| %7s | %33s | %10s | %10s | %25s |\n-----------------------------------------------------------------------------------------------------\n", "(index)", "value", "type_name", "type_value", "expanded_types");
	// while (tokens != NULL)
	// {
	// 	token = (t_token *)tokens->content;
	// 	printf("| %7zu | %33s | %10s | %10i | %25s |\n", i, token->value, token_type_as_str(token->type), token->type, all_types(token->type));
	// 	tokens = tokens->next;
	// 	i++;
	// }
	// printf("-----------------------------------------------------------------------------------------------------\n");
	return (0);
}
