/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_get_valid_path.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 15:19:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/03/23 13:25:28 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <unistd.h>
#include <stdlib.h>

static char	*find_valid_path(char **all_absolute_paths)
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
 * Searches for a valid path to a command
 * @param command pointer to `char *`
 * @return A pointer to a valid path allocated with malloc()
 * - if no valid path cannot be found, exit(127) is called 
 * with the appropriate error message
 */
char	*cmd_get_valid_path(const char *command)
{
	const char	*paths = getenv("PATH");
	char		**splitted_paths;
	char		*valid_path;

	valid_path = NULL;
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	if (command[0] != '.' && command[0] != '\0')
	{
		splitted_paths = ft_split(paths, ':');
		splitted_paths = add_command_to_paths(splitted_paths, command);
		valid_path = find_valid_path(splitted_paths);
	}
	if (valid_path == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(ERROR_CODE_NO_FILE_FOUND);
	}
	return (valid_path);
}
