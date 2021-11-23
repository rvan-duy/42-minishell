/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:38:22 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/11/02 13:30:25 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

# define CHILD_PROCESS 0
# define NO_BUILTIN 2

int	execute_line(t_cmd_node *nodes, t_env_var *envp);

#endif
