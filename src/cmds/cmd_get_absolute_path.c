/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_get_absolute_path.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 15:19:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/16 14:47:29 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static char	*find_valid_path(char **all_absolute_paths, const char *command)
{
	size_t	i;
	char	*path;

	i = 0;
	path = NULL;
	while (all_absolute_paths[i])
	{
		if (access(all_absolute_paths[i], X_OK) > -1)
		{
			path = ft_strdup(all_absolute_paths[i]);
			if (path == NULL)
				exit(EXIT_FAILURE);
			break ;
		}
		i++;
	}
	if (access(command, X_OK) > -1)
	{
		path = ft_strdup(command);
		if (path == NULL)
			exit(EXIT_FAILURE);
	}
	ft_free_arr((void ***)&all_absolute_paths);
	return (path);
}

static char	**add_command_to_paths(char **split_paths, const char *command)
{
	const size_t	split_paths_len = ft_array_len((void **)split_paths);
	char			**combined_path;
	size_t			i;

	combined_path = ft_calloc(split_paths_len + 1, sizeof(char *));
	if (combined_path == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (split_paths[i])
	{
		combined_path[i] = ft_strjoin_three(split_paths[i], "/", command);
		if (combined_path[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	ft_free_arr_n((void ***)&split_paths, split_paths_len);
	return (combined_path);
}

/**
 * Searches for the absolute path to a command
 * @param command pointer to `char *`
 * @return A pointer to the absolute path allocated with malloc()
 * - if no absolute path can be found, exit() is called 
 * with the appropriate error message
 */
char	*cmd_get_absolute_path(const char *command)
{
	const char	*paths = getenv("PATH");
	char		**splitted_paths;
	char		*valid_path;

	splitted_paths = ft_split(paths, ':');
	if (splitted_paths == NULL)
		exit(EXIT_FAILURE);
	splitted_paths = add_command_to_paths(splitted_paths, command);
	valid_path = find_valid_path(splitted_paths, command);
	if (valid_path == NULL)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	return (valid_path);
}
