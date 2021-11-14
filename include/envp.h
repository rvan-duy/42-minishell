/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:06:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/14 14:33:29 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "structs.h"
# include <stdlib.h>

/* 
 * List functions 
 */

char		**env_list_to_arr(t_env_var *envp);
size_t		env_list_len(t_env_var *envp);
t_env_var	*env_arr_to_list(char **envp);
t_env_var	*env_list_dup(t_env_var *envp);

/*
 * Node functions
 */

void		env_node_add(t_env_var **head, t_env_var *new);
void		env_node_del(const char *name, t_env_var **head);
t_env_var	*env_get_var(const char *name, t_env_var *envp);
t_env_var	*env_node_dup(t_env_var *node);
t_env_var	*env_node_last(t_env_var *head);
t_env_var	*env_node_new(const char *env_var);

#endif
