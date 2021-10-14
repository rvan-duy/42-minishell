/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 15:46:40 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/14 11:15:15 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utilities.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

int	builtin_echo(t_cmd_node *nodes);
int	builtin_cd(t_cmd_node *nodes);
int	builtin_pwd(void);

#endif
