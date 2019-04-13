/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/13 16:05:09 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>

void	exec_prompt(t_list *env, t_opt *opt, t_build *build)
{
	char	*line;
	int		status;

	status = 1;
	credit(build);
	while (status)
	{
		init_prompt();
		if (!(status = get_next_line(STDIN_FILENO, &line)))
			break ;
		helper(env, opt, build, line);
		free(line);
	}
	free(line);
}

int		main(int ac, char **av, char **environ)
{
	t_build build;
	t_opt	opt;
	t_list	*env;
	char *line = NULL; //For logging

	init_build(&build);
	ft_bzero(&opt, sizeof(t_opt));
	if (!(get_opt(ac, av, &opt)))
		return (exit_status(&opt, FT, FL, LN));
	if (!(env = set_env(environ)))
	{
		opt.fail = 1;
		helper(env, &opt, &build, line);
		return (exit_status(&opt, FT, FL, LN));
	}
	helper(env, &opt, &build, line);
	signal_handler();
	if (!opt.v && !opt.h)
		exec_prompt(env, &opt, &build);
	free_list(env);
	return (exit_status(&opt, FT, FL, LN));
}
