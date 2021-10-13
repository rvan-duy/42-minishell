/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 11:48:54 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/13 11:11:08 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "libft.h"
# include "structs.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>

pid_t		safe_fork(void);
t_pipefds	safe_create_pipe(void);
void		safe_close(int fd);
int			safe_open(const char *filename, int oflag);
void		safe_dup2(int fildes1, int fildes2);

void		check_acces(const char *cmd, int oflag);
t_bool		contains_flag(const char *string, const char *flag);

#endif
