/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 15:45:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/19 16:34:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * e_type: type of in-/output
 * file_name: file name
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

/**
 * cmd: command/file to execute
 * argv: { argv0, argv1, ... }
 * pipe_to: next command in series, NULL if final
 * files: array of in / out files (t_files)
 */
typedef struct s_cmd_node
{
	char				*cmd;
	char				**argv;
	struct s_cmd_node	*pipe_to;
	t_files				**files;
}	t_cmd_node;

typedef enum e_status
{
	FAILURE,
	SUCCESS
}	t_status;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_arg_type
{
	LITERAL,
	VARIABLE
}	t_arg_type;

typedef struct s_arg
{
	t_arg_type		type;
	char			*value;
	struct s_arg	*next_part;
}	t_arg;

#endif
