/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:38:22 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/12 13:48:22 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"
# include "utilities.h"
# include "builtins.h"
# include <stdbool.h>

# define CHILD_PROCESS 0
# define NO_BUILTIN 1

int	execute_line(t_cmd_node *nodes, t_files *files, char **envp);

#endif
