/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 15:46:40 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 14:54:45 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

t_status	builtin_pwd(void);
int			builtin_echo(t_cmd_node *nodes);
t_status	builtin_env(t_env_var *envp);
t_status	builtin_cd(t_cmd_node *nodes, t_env_var *envp);
t_status	buitlin_unset(t_cmd_node *nodes, t_env_var *envp);
t_status	builtin_export(t_cmd_node *nodes, t_env_var *envp);

#endif
