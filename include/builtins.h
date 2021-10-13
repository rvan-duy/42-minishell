/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 15:46:40 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/13 15:18:05 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utilities.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

int	echo(t_cmd_node *nodes);
// cd
int	pwd(void);

#endif
