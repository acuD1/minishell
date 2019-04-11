/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:33 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/11 14:25:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_db	*fetch_db(t_db *db, char *environ)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(environ, '=');
	db->symbol = ft_strdup(split[0]);
	db->value = ft_strdup(split[1]);
	while (split[i])
		free(split[i++]);
	free(split);
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
