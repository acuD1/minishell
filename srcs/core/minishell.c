/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 10:35:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int		main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_list	*env;

	if (!(build(ac, av)))
	{
		printf("?\n");
		return (EXIT_FAILURE);
	}
	if (!(env = set_env(environ)))
	{
		logger(env, environ);
		return (0);
	}
	//exec_prompt(env);
	logger(env, environ);
	free_list(env);
	return (EXIT_SUCCESS);
}
