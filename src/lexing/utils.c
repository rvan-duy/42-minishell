/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 13:06:41 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/13 14:13:14 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_bool	ms_issep(char c)
{
	return (c == ' ' || c == '\t');
}

t_bool	ms_isquote(char c)
{
	return (c == '\'' || c == '"');
}
