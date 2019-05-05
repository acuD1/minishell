/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:46:59 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 14:44:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	usage(char *av, int i, t_core *shell)
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
	shell->flag.usage = 1;
	return (0);
}

static int	fill_opt(t_core *shell, char av)
{
	if (!(ft_strchr("-hvd", av)))
		return (0);
	if (av == 'v')
	{
		shell->opt.h = 0;
		shell->opt.v = 1;
	}
	if (av == 'h')
	{
		shell->opt.h = 1;
		shell->opt.v = 0;
	}
	if (av == 'd')
		shell->opt.d = 1;
	return (1);
}

static void	get_logger(char **av, t_core *shell, int i)
{
	if (!(av[i]))
	{
		shell->logger = ft_strdup(DEFAULT_TTY);
		return ;
	}
	shell->logger = ft_strdup(av[i]);
}

int			get_opt(int ac, char **av, t_core *shell)
{
	int		i;
	int		j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] == '-' && av[i][2])
			return (usage(av[i], i, shell));
		else if (av[i][0] == '-' && av[i][1] == '-')
		{
			i++;
			break ;
		}
		else if (av[i][0] == '-' && av[i][1])
		{
			while (av[i][j])
				if (!(fill_opt(shell, av[i][j++])))
					return (usage(av[i], i, shell));
		}
		else
			break ;
	}
	get_logger(av, shell, i);
	return (1);
}
