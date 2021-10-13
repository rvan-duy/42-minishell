/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 12:11:37 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/12 18:23:18 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

t_pipefds	safe_create_pipe(void)
{
	t_pipefds	result;
	int			pipefds[2];

	if (pipe(pipefds) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	result.read = pipefds[0];
	result.write = pipefds[1];
	return (result);
}

void	safe_close(int fd)
{
	if (close(fd) < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": Close (fd: ", STDERR_FILENO);
		ft_putnbr_fd(fd, STDERR_FILENO);
		ft_putendl_fd(")", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

int	safe_open(const char *filename, int oflag)
{
	int	fd;

	if (filename == NULL)
		return (-1);
	fd = open(filename, oflag, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	safe_dup2(int fildes1, int fildes2)
{
	if (fildes1 < 0 || fildes2 < 0)
		return ;
	if (dup2(fildes1, fildes2) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}
