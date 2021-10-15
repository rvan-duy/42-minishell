/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:48:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 12:48:45 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_H
# define SAFE_H

# include "structs.h"
# include <unistd.h>

pid_t		safe_fork(void);
t_pipefds	safe_create_pipe(void);
void		safe_close(int fd);
int			safe_open(const char *filename, int oflag);
void		safe_dup2(int fildes1, int fildes2);
void		safe_chdir(const char *dir);

#endif
