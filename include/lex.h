/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 13:51:33 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/13 13:58:48 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "structs.h"

t_arg		*lex_arg(char *str);
char		*get_arg(char *part, char **after_part);
t_status	set_arg(t_arg_type type, char *value, t_arg **arg);
int			lex_single(char *str, t_arg ***arg);
int			lex_var(char *str, t_arg ***arg);
int			lex_double(char *str, t_arg ***arg);
int			lex_none(char *str, t_arg ***arg);

#endif
