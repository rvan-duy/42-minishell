/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:38:22 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/09 15:06:16 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

# define EXECUTE_SUCCESS 0
# define EXECUTE_FAILURE 1
# define NO_BUILTIN 2

t_status	execute_line(t_cmd_node *nodes, t_env_var *envp);

#endif
