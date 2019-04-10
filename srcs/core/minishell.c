/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/07 13:35:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
t_list	*set_environ(t_list *env, char **environ)
{
	t_db	db;

	env = NULL;



}*/

int		main(void)
{
	/*
	t_list	*env;

	env = set_environ(env, environ);
	//exec_prompt(m_sh);*/
	char **test;
	int		i;

	i = 0;
	test = environ;
	while (test[i])
		ft_mprintf(STDERR_FILENO, "%s\n", test[i++]);
	build();
	return (0);
}
