/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thing.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 13:55:40 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/12/01 14:58:10 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THING_H
# define THING_H

# include "structs.h"

t_symbol			*add_symbol(t_symbol_type type, t_list **symbols);
t_symbol_type		get_symbol_type(char *str);
typedef t_status	(*t_finish_symbol)(char **str, t_list **symbols);
t_finish_symbol		*get_finish_table(void);
t_list				*thing(char *str, char **next_part);
typedef void		(*t_fix_symbol)(t_list **arg_symbols, t_list **files);
void				fix_single(t_list **arg_symbol, t_list **files);
t_bool				can_be_literalized(t_list *arg_symbol);
t_fix_symbol		*get_fix_table(void);
void				fix_thing(t_list **arg_symbols, t_list **files);

t_status			finish_pipe(char **str, t_list **symbols);
t_status			finish_redirect(char **str, t_list **symbols);
t_status			finish_double_redirect(char **str, t_list **symbols);
t_status			finish_double_quoted(char **str, t_list **symbols);
t_status			finish_single_quoted(char **str, t_list **symbols);
t_status			finish_variable(char **str, t_list **symbols);
t_status			finish_literal(char **str, t_list **symbols);

void				fix_double_quoted(t_list **arg_symbols, t_list **files);
void				fix_single_quoted(t_list **arg_symbols, t_list **files);
void				fix_pipe(t_list **arg_symbols, t_list **files);
void				fix_redirect(t_list **arg_symbols, t_list **files);
void				fix_double_redirect(t_list **arg_symbols, t_list **files);
void				fix_variable(t_list **arg_symbols, t_list **files);
void				fix_literal(t_list **arg_symbols, t_list **files);

t_bool				is_pipe(char *str);
t_bool				is_redirect(char *str);
t_bool				is_double_redirect(char *str);
t_bool				is_single_quoted(char *str);
t_bool				is_double_quoted(char *str);
t_bool				is_variable(char *str);
t_bool				is_literal(char *str);
t_bool				is_end_of_string(char *str);

void				do_thing2(char *cmd, t_cmd_node **node);

#endif
