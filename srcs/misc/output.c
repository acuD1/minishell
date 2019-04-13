/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:23:07 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/13 14:51:16 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(void)
{
	ft_mprintf(STDOUT_FILENO, "[?]>");
}

void	credit(t_build *build)
{
	ft_mprintf(STDOUT_FILENO,
		"%s|%sv.%d_%d%s|%s minishell by arsciand :)%s\n\n",
		C_G, C_X, build->version, build->number, C_G, C_Y, C_X);
}
