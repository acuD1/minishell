/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:58:32 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/15 11:40:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_db	*fetch_db(t_db *env_db, const char *s)
{
	size_t	len;

	len = ft_strclen(s, '=');
	env_db->symbol = ft_strsub(s, 0, len);
	env_db->value = ft_strdup(s + len + 1);
	return (env_db);
}
