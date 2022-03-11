/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 13:28:01 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/11 12:24:04 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	change_signals(void (*sigint)(int), void (*sigquit)(int));
void	signal_handler(int sig);
void	signal_handler_heredoc(int sig);

#endif
