/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:28:00 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 10:51:44 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_file(char **path, char *filename)
{
	DIR				*content;
	struct dirent	*dir;
	int				i;

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

void		get_path(t_core *shell, char *filename)
{
	t_list	*env;
	char	**path;
	char	*tmp;

	env = shell->env;
	if (!filename)
		return ;
	if (filename[0] == '.' || filename[0] == '/')
	{
		shell->bin_path = ft_strdup(filename);
		return ;
	}
	tmp = ft_strjoin("/", filename);
	while (env)
	{
		if (ft_strequ(ENV_DB->symbol, "PATH"))
		{
			path = ft_strsplit(ENV_DB->value, ':');
			shell->bin_path = ft_strjoin_free(find_file(path, filename),
									tmp, 3);
			free_tab(path);
			return ;
		}
		env = env->next;
	}
}
