/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:50:30 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/08 14:02:21 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "structs.h"
# include <stdbool.h>

char		*cmd_get_valid_path(const char *command, t_env_var *envp);
char		**cmd_create_execve_array(char *command, char **arguments);
void		cmd_exec_single_file(t_cmd_node *nodes, t_env_var *envp, \
				int write_fd);
void		cmd_exec_multiple_files(t_cmd_node *nodes, t_env_var *envp);
t_status	cmd_expand_heredoc(t_cmd_node *nodes);
void		cmd_io_redirections(t_list *files, bool in_child);

#endif
