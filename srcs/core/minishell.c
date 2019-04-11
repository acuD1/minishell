/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/11 14:59:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_list	*env;

	if (!(build(ac, av)))
		return (0);
	if (!(env = set_env(environ)))
		return (0);
	logger(env, environ);
	free_list(env);
	return (0);
}
