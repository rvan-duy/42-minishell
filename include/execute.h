/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:38:22 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/01 16:40:20 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

# define CHILD_PROCESS 0

# define ERROR 1
# define NO_BUILTIN 2

int	execute_line(t_cmd_node *nodes, t_env_var *envp);

#endif
