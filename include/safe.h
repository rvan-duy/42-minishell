/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 12:48:05 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 11:48:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_H
# define SAFE_H

# include "structs.h"
# include <unistd.h>
# include <stdbool.h>

# define CHILD_PROCESS 0

pid_t		safe_fork(void);
pid_t		safe_wait(int *arg);
t_pipefds	safe_create_pipe(void);
int			safe_open(const char *filename, int oflag, bool in_child);
void		safe_close(int fd);
void		safe_dup2(int fildes1, int fildes2);
int			safe_chdir(const char *dir);
void		safe_check_access(char *absolute_path, const char *cmd, int oflag);

#endif
