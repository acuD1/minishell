/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:33 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 15:47:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_db	*fetch_db(t_db *db, char *environ)
{
	size_t len;

	len = ft_strclen(environ, '=');
	db->symbol = ft_strsub(environ, 0, len);
	db->value = ft_strsub(environ, len + 1, ft_strlen(environ));
	return (db);
}

t_list	*set_env(char **environ)
{
	t_db	db;
	t_list	*env;
	int		i;

	i = 0;
	env = NULL;
	ft_bzero(&db, sizeof(t_db));
	while (environ[i])
	{
		ft_lstpushback(&env,
			ft_lstnew(fetch_db(&db, environ[i]), sizeof(t_db)));
		i++;
	}
	return (env);
}
