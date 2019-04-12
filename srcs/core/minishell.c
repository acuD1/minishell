/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 15:01:16 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	t_opt	opt;
	t_list	*env;

	ft_bzero(&opt, sizeof(t_opt));
	if (!(get_opt(ac, av, &opt)))
		return (exit_status(&opt, FT, FL, LN));
	if (!(env = set_env(environ)))
	{
		opt.fail = 1;
		helper(env, &opt);
		return (exit_status(&opt, FT, FL, LN));
	}
	helper(env, &opt);
	free_list(env);
	return (exit_status(&opt, FT, FL, LN));
}
