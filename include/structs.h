/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 15:45:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/11/16 14:24:22 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define PROGRAM_NAME "minishell"

# define ERROR_CODE_NUMERIC_ARGS 255

/**
 * file_in: file to put on stdin (NULL if no file specified)
 * file_out: file to put on stdout (NULL if no file specified)
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
 * files: in and out files for that cmd
 */
typedef struct s_cmd_node
{
	char				*cmd;
	char				**argv;
	struct s_cmd_node	*pipe_to;
	t_files				**files;
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

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

#endif
