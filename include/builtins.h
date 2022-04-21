/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 15:46:40 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/04/21 15:03:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"
# include <stdbool.h>

# define VALID 0
# define INVALID 1
# define NO_BUILTIN 2

bool		builtin_check(const char *cmd);
int			builtin_check_and_exec(t_cmd_node *nodes, t_env_var **envp);

t_status	builtin_pwd(void);
t_status	builtin_env(t_env_var *envp);
t_status	builtin_echo(t_cmd_node *nodes);
t_status	builtin_exit(t_cmd_node *nodes);
t_status	builtin_cd(t_cmd_node *nodes, t_env_var **envp);
t_status	builtin_unset(t_cmd_node *nodes, t_env_var **envp);
t_status	builtin_export(t_cmd_node *nodes, t_env_var **envp);
t_status	list_export(t_env_var **envp);

#endif
