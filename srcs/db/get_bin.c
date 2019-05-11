/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:28:00 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 10:49:41 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

static char	*find_file(char **path, const char *filename)
{
	DIR				*content;
	struct dirent	*dir;
	size_t			i;

	i = 0;
	while (path[++i])
	{
		if (!(content = opendir(path[i])))
		{
			ft_mprintf(STDERR_FILENO, "%sFailed opendir(%s) !\n%s",
				C_R, path[i], C_X);
			continue;
		}
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
	}
	return (NULL);
}

char		*get_bin(t_core *shell, const char *filename)
{
	t_list	*env;
	char	**path;

	path = NULL;
	env = shell->env;
	if (!filename || (filename[0] == '.' && !filename[1]))
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
