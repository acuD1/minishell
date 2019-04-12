/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:46:59 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 09:29:04 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define XSTR(x) #x
#define STR(x) XSTR(x)

int		usage(char *av, int i)
{
	while (av[i])
	{
		if (av[i] == 'h')
			ft_mprintf(1, "Helps not defined\n");
		if (!(ft_strchr("-vh", av[i])))
		{
			ft_mprintf(1, "minishell: illegal option -%c\n", av[i]);
			ft_putendl("usage : ./minishell [-vh]");
			break ;
		}
		i++;
	}
	return (0);
}

int		build(int ac, char **av)
{
	t_build	build;
	int		i;
	int		j;

	i = 0;
	ft_bzero(&build, sizeof(t_build));
	build.version = BUILD + 1;
	build.date = DATE;
	ft_strcpy(build.branch, STR(BRANCH));
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] != 'v')
		{
			usage(av[i], i);
			return (0);
		}
		else if (av[i][0] == '-' && av[i][1] == 'v')
		{
			ft_mprintf(1, "minishell v.%d_%d_%s\n",
				build.version, build.date, build.branch);
			return (0);
		}
	}
	return (1);
}
