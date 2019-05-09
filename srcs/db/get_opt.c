/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:46:59 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 15:18:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int8_t	usage(char *av, int i)
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
	return (FAILURE);
}

static int8_t	fill_opt(t_core *shell, char av)
{
	if (!(ft_strchr("-hvd", av)))
		return (FAILURE);
	if (av == 'v')
		shell->opt |= OPT_VERS;
	else if (av == 'h')
		shell->opt |= OPT_HELP;
	else if (av == 'd')
		shell->opt |= OPT_DEBG;
	return (SUCCESS);
}

int8_t			get_opt(int ac, char **av, t_core *shell)
{
	int		i;
	size_t	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] == '-' && av[i][2])
			return (usage(av[i], i));
		else if (av[i][0] == '-' && av[i][1] == '-')
		{
			i++;
			break ;
		}
		else if (av[i][0] == '-')
		{
			while (av[i][j])
				if (fill_opt(shell, av[i][j++]) == FAILURE)
					return (usage(av[i], i));
		}
		else
			break ;
	}
	open_logger_fd(shell, av[i]);
	return (SUCCESS);
}
