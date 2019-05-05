/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:23:07 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 14:45:37 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(void)
{
	ft_mprintf(STDOUT_FILENO, "[?]>");
}

void	credit(t_core *shell)
{
	ft_mprintf(STDOUT_FILENO,
		"%s|%sv.%d_%d%s|%s minishell%s\n\n",
		C_G, C_X, shell->build.version, shell->build.patch, C_G, C_Y, C_X);
}

void	print_opt(t_core *shell)
{
	if (shell->opt.h)
	{
		ft_putendl_fd("Minishell by arsciand\nto run : ./minishell",
			STDOUT_FILENO);
		exit(1);
	}
	if (shell->opt.v)
	{
		ft_mprintf(STDOUT_FILENO, "minishel v.%d_%d_%d\n",
			shell->build.version, shell->build.patch, shell->build.date);
		exit(1);
	}
}
