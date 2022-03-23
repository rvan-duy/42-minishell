/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 15:45:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/23 10:47:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

# define PROGRAM_NAME "minishell"

# define ERROR_CODE_NUMERIC_ARGS 255
# define ERROR_CODE_NO_FILE_FOUND 127
# define ERROR_CODE_FOUND_BUT_NOT_EXECUTED 126

// Exit to the exit status of the most recently executed foreground pipeline.
unsigned char	g_exit_status;

/**
 * @param e_type type of in-/output
 * @param file_name file name
 */
typedef struct s_file
{
	enum {
		REDIRECT_INPUT,
		REDIRECT_OUTPUT,
		HERE_DOCUMENT,
		APPENDING_REDIRECT_OUTPUT
	}	e_type;
	char	*file_name;
}	t_file;

/**
 * @param cmd command/file to execute
 * @param argv { argv0, argv1, ... }
 * @param pipe_to next command in series, NULL if final
 * @param files list of in / out files (t_file)
 */
typedef struct s_cmd_node
{
	char				*cmd;
	char				**argv;
	struct s_cmd_node	*pipe_to;
	t_list				*files;
}	t_cmd_node;

typedef struct s_pipefds
{
	int	read;
	int	write;
}	t_pipefds;

typedef enum e_status
{
	SUCCESS,
	FAILURE
}	t_status;

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

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

#endif
