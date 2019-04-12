/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:46:59 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 15:05:20 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		usage(char *av, int i, t_opt *opt)
{
	while (av[i])
	{
		if (!(ft_strchr("-vhd", av[i])))
		{
			ft_mprintf(STDOUT_FILENO, "minishell: illegal option -%c\n", av[i]);
			ft_putendl("usage : ./minishell [-vhd] [Logger]");
			break ;
		}
		i++;
	}
	opt->fail = 1;
	opt->usage = 1;
	return (0);
}

static int		fill_opt(t_opt *opt, char av)
{
	if (!(ft_strchr("-hvd", av)))
		return (0);
	if (av == 'v')
	{
		opt->v = 1;
		opt->h = 0;
	}
	if (av == 'h')
	{
		opt->h = 1;
		opt->v = 0;
	}
	if (av == 'd')
		opt->d = 1;
	return (1);
}

void	get_logger(char **av, t_opt *opt, int i)
{
	if (!(av[i]))
	{
		opt->logger = ft_strdup(DEFAULT_TTY);
		return ;
	}
	opt->logger = ft_strdup(av[i]);
}

int		get_opt(int ac, char **av, t_opt *opt)
{
	int		i;
	int		j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] == '-' && av[i][2])
			return (usage(av[i], i, opt));
		else if (av[i][0] == '-' && av[i][1] == '-')
		{
			i++;
			break ;
		}
		else if (av[i][0] == '-' && av[i][1])
		{
			while (av[i][j])
				if (!(fill_opt(opt, av[i][j++])))
					return (usage(av[i], i, opt));
		}
		else
			break ;
	}
	get_logger(av, opt, i);
	return (1);
}
