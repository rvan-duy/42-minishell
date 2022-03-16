/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:50:30 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/16 11:58:41 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "structs.h"

# define SUCCESFULLY_EXECUTED_BUILTIN 0

char	    *cmd_get_valid_path(const char *command);
char	    **cmd_create_execve_array(char *command, char **arguments);
void	    cmd_exec_single_file(t_cmd_node *nodes, t_env_var *envp, int write_fd);
void	    cmd_exec_multiple_files(t_cmd_node *nodes, t_env_var *envp);
t_status	cmd_expand_heredoc(t_cmd_node *nodes);
void	    cmd_redirect_stdin(t_list *files);
void	    cmd_redirect_stdout(t_list *files);

#endif
