/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:33 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 15:37:49 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

static t_db		*fetch_db(t_db *db, const char *environ)
{
	size_t	len;

	len = ft_strclen(environ, '=');
	db->symbol = ft_strsub(environ, 0, len);
	db->value = ft_strdup(environ + len + 1);
	return (db);
}

static int8_t	set_default_env(t_core *shell, t_db *db)
{
	char	*default_environ[4];
	char	pwd[PATH_MAX];
	size_t	i;

	i = 0;
	*default_environ = NULL;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		default_environ[0] = ft_strjoin("PWD=", pwd);
	else
		return (FAILURE);
	default_environ[1] = DEFAULT_SHLVL;
	default_environ[2] = DEFAULT_LA;
	default_environ[3] = NULL;
	while (default_environ[i])
	{
		ft_lstpushback(&shell->env,
			ft_lstnew(fetch_db(db, default_environ[i]), sizeof(t_db)));
		i++;
	}
	ft_strdel(&default_environ[0]);
	return (SUCCESS);
}

int8_t			set_env(t_core *shell, char **environ)
{
	t_db	db;
	size_t	i;

	i = 0;
	ft_bzero(&db, sizeof(t_db));
	if (*environ == NULL)
		return (set_default_env(shell, &db));
	while (environ[i])
	{
		ft_lstpushback(&shell->env,
			ft_lstnew(fetch_db(&db, environ[i]), sizeof(t_db)));
		i++;
	}
	if (shell->env == NULL)
		return (FAILURE);
	return (SUCCESS);
}
