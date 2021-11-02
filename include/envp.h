/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:06:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/02 11:42:25 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "structs.h"

t_status	envp_get_var(char *var, char **envp, char **dst);
t_status	envp_add_3(char ***envp, const char *name, const char *value);
t_status	envp_add_2(char ***envp, const char *var);
t_status	envp_del(char **envp, const char *name);

// NEW VERSION LOL
t_env_var	*env_dup(char **envp);
t_env_var	*env_new(const char *env_var);
t_env_var	*env_last(t_env_var *head);
void		env_add(t_env_var **head, t_env_var *new);

#endif
