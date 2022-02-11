/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 16:50:30 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/11 13:38:58 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "structs.h"

char		*cmd_get_absolute_path(const char *command);
char		**cmd_create_execve_array(char *command, char **arguments);
t_status	cmd_exec_file(t_cmd_node *nodes, t_env_var *envp);
void		cmd_redirect_stdin(t_files **files);
void		cmd_redirect_stdout(t_files **files);

#endif
