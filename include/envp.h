/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:06:25 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 12:56:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "structs.h"

char		**envp_dup(char **envp);
t_status	envp_get_var(char *var, char *envp[], char **dst);

#endif
