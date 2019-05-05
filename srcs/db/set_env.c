/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:33 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 10:48:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_db		*fetch_db(t_db *db, char *environ)
{
	size_t	len;

	len = ft_strclen(environ, '=');
	db->symbol = ft_strsub(environ, 0, len);
	db->value = ft_strdup(environ + len + 1);
	return (db);
}

static t_list	*fetch_default(t_list *env, t_db *db, int i)
{
	char	*default_environ[4];
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		default_environ[0] = ft_strjoin_free(ft_strdup("PWD="),
									ft_strdup(pwd), 3);
	else
		return (NULL);
	default_environ[1] = DEFAULT_SHLVL;
	default_environ[2] = DEFAULT_LA;
	default_environ[3] = NULL;
	while (default_environ[i])
	{
		ft_lstpushback(&env,
			ft_lstnew(fetch_db(db, default_environ[i]), sizeof(t_db)));
		i++;
	}
	free(default_environ[0]);
	return (env);
}

t_list			*set_env(char **environ)
{
	t_db	db;
	t_list	*env;
	int		i;

	i = 0;
	env = NULL;
	ft_bzero(&db, sizeof(t_db));
	if (!(*environ))
		return (fetch_default(env, &db, i));
	while (environ[i])
	{
		ft_lstpushback(&env,
			ft_lstnew(fetch_db(&db, environ[i]), sizeof(t_db)));
		i++;
	}
	return (env);
}
