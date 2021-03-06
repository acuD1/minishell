/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:28:00 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/29 10:49:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

static char	*find_file(char **path, const char *filename)
{
	DIR				*content;
	struct dirent	*dir;
	size_t			i;

	i = 0;
	while (path[i])
	{
		if (!(content = opendir(path[i])))
			continue;
		while (content && (dir = readdir(content)))
		{
			if (ft_strequ(filename, dir->d_name))
			{
				closedir(content);
				return (ft_strdup(path[i]));
			}
			continue;
		}
		closedir(content);
		i++;
	}
	return (NULL);
}

char		*get_bin(t_core *shell, t_list *env, const char *filename)
{
	char		**path;
	struct stat	stat;

	path = NULL;
	if ((lstat(filename, &stat) == 0 && S_ISDIR(stat.st_mode))
		|| !filename || (filename[0] == '.' && !filename[1]))
		return (NULL);
	if ((filename[0] == '.' || filename[0] == '/') && filename[1])
		return (shell->bin = ft_strdup(filename));
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "PATH") == TRUE)
		{
			path = ft_strsplit(((t_db*)(env->content))->value, ":");
			shell->bin = ft_strjoinf(find_file(path, filename),
								ft_strjoin("/", filename), FREE_ALL);
			ft_free_tab(&path);
		}
		env = env->next;
	}
	return (shell->bin);
}
