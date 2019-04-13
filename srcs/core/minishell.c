/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/13 11:50:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_prompt(t_list *env, t_opt *opt, t_build *build)
{
	char	*line;
	int		status;

	status = 1;
	while (status)
	{
		ft_mprintf(STDOUT_FILENO, "%s[%sv.%d_%d%s]%s> %s",
			C_G, C_X, build->version, build->number, C_G, C_B, C_X);
		if (!(status = get_next_line(STDIN_FILENO, &line)))
			exit(42);
		helper(env, opt, build, line);												//LOG
		free(line);
	}
}

int		main(int ac, char **av, char **environ)
{
	t_build build;
	t_opt	opt;
	t_list	*env;
	//
	char *line = NULL;																//LOG
	//

	init_build(&build);
	ft_bzero(&opt, sizeof(t_opt));
	if (!(get_opt(ac, av, &opt)))
		return (exit_status(&opt, FT, FL, LN));
	if (!(env = set_env(environ)))
	{
		opt.fail = 1;
		helper(env, &opt, &build, line);											//LOG
		return (exit_status(&opt, FT, FL, LN));
	}
	helper(env, &opt, &build, line);												//LOG
	if (!opt.v && !opt.h)
		exec_prompt(env, &opt, &build);
	free_list(env);
	return (exit_status(&opt, FT, FL, LN));
}
