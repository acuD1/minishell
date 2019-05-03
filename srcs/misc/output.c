/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:23:07 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 13:03:47 by arsciand         ###   ########.fr       */
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
