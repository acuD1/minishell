/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:53:15 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/15 10:53:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	echo_builtin(char **tokens)
{
	size_t	i;
	uint8_t	no_newline;

	i = 1;
	no_newline = 0;
	if (ft_strequ(tokens[i], "-n"))
	{
		i = 2;
		no_newline = TRUE;
	}
	while (tokens[i])
	{
		ft_mprintf(STDOUT_FILENO, "%s", tokens[i]);
		i++;
		if (tokens[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (no_newline == FALSE)
		write(STDOUT_FILENO, "\n", 1);
}
