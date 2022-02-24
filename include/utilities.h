/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:48:54 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/23 17:10:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "structs.h"
# include <stdbool.h>

t_status	get_env_var(char *var, char *envp[], char **dst);
bool		ms_issep(char c);
bool		ms_isquote(char c);
bool		contains_flag(const char *string, const char *flag);

#endif
