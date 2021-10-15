/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:48:54 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 13:47:23 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "structs.h"

void		check_acces(const char *cmd, int oflag);
t_bool		contains_flag(const char *string, const char *flag);

#endif
