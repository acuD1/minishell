/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:40:28 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/14 12:56:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <time.h>

static void	print_env_db(t_list *env, int fd)
{
	int		i;

	i = 0;
	ft_putendl_fd("DEBUF FOR ENV_DB ->", fd);
	if (!(env))
		ft_mprintf(fd, "%sEMPTY%s\n", C_R, C_X);
	while (env)
	{
		ft_mprintf(fd, "%sENV_DB[%s%d%s]\n%sS = |%s|\n%sV = |%s|%s\n",
			C_Y, C_G, i, C_Y, C_M, ENV_DB->symbol, C_C, ENV_DB->value, C_X);
		env = env->next;
		i++;
	}
}

static void	print_opt(t_opt *opt, t_build *build)
{
	if (opt->h)
		ft_putendl_fd("Minishell by arsciand\nto run : ./minishell",
			STDOUT_FILENO);
	if (opt->v)
		ft_mprintf(STDOUT_FILENO, "minishel v.%d_%d_%d\n",
			build->version, build->number, build->date);
}

int		open_logger(t_opt *opt)
{
	int		fd;

	if ((fd = open(opt->logger,
		O_WRONLY | O_APPEND | O_CREAT | O_NOFOLLOW, 0600)) == -1)
	{
		opt->stop = 1;
		ft_mprintf(1, "%sFailed open %s for debug !%s\n",
			C_R, opt->logger, C_X);
		return (0);
	}
	return (fd);
}

void		helper(t_list *env, t_opt *opt, t_build *build, char *line)
{
	struct tm	*timeinfo;
	time_t		rawtime;
	int			fd;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if (!(fd = open_logger(opt)))
		return ;
	print_opt(opt, build);
	if (!opt->d)
		return ;
	ft_mprintf(fd, "\n\n>\n%sLOGGING...%s\n", C_B, C_X);
	print_env_db(env, fd);
	ft_mprintf(fd, "\nline = |%s|\n\n", line);
	ft_mprintf(fd, "LOGGER FOR MINISHELL V.%d_%d : %s",
		build->version, build->number, asctime(timeinfo));
}
