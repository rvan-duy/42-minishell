/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 15:45:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/30 14:55:19 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"
# include <stdbool.h>

/**
 * @param e_type type of in-/output
 * @param file_name file name
 */
typedef struct s_files
{
	enum {
		IN,
		OUT,
		HEREDOC_IN,
		HEREDOC_OUT
	}	e_type;
	char	*file_name;
}	t_files;

// /**
//  * @param cmd command/file to execute
//  * @param argv { argv0, argv1, ... }
//  * @param pipe_to next command in series, NULL if final
//  * @param files array of in / out files (t_files)
//  */
// typedef struct s_cmd_node
// {
// 	char				*cmd;
// 	char				**argv;
// 	struct s_cmd_node	*pipe_to;
// 	t_files				**files;
// }	t_cmd_node;

/**
 * @param cmd command/file to execute
 * @param argv { argv0, argv1, ... }
 * @param pipe_to next command in series, NULL if final
 * @param files list of in / out files (t_files)
 */
typedef struct s_cmd_node
{
	char				*cmd;
	char				**argv;
	struct s_cmd_node	*pipe_to;
	t_list				*files;
}	t_cmd_node;

/**
 * @param files list of (t_file)'s
 */
typedef struct s_cmd_data
{
	t_list	*files;
}	t_cmd_data;

typedef enum e_status
{
	FAILURE,
	SUCCESS
}	t_status;

typedef bool	t_bool;

// TODO: Check if even used anymore
typedef enum e_arg_type
{
	LITERAL,
	VARIABLE
}	t_arg_type;

// TODO: Check if even used anymore
typedef struct s_arg
{
	t_arg_type		type;
	char			*value;
	struct s_arg	*next_part;
}	t_arg;

typedef enum e_symbol_type
{
	STRUCT_PIPE,
	STRUCT_REDIRECT,
	STRUCT_DOUBLE_REDIRECT,
	STRUCT_VARIABLE,
	STRUCT_DOUBLE_QUOTED,
	STRUCT_SINGLE_QUOTED,
	STRUCT_LITERAL,
	END_OF_STRING
}	t_symbol_type;

typedef struct s_symbol
{
	t_symbol_type	type;
	char			*value;
}	t_symbol;

#endif
