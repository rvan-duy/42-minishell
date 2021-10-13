/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 13:24:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/13 16:48:01 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "structs.h"

t_status	get_env_var(char *var, char *envp[], char **dst);
t_bool		ms_issep(char c);
t_bool		ms_isquote(char c);

#endif
