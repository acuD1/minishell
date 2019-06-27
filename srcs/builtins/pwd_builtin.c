/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 10:30:27 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 13:58:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	pwd_builtin(void)
{
	char	pwd[PATH_MAX];

	if (!(getcwd(pwd, sizeof(pwd))))
	{
		ft_mprintf(STDERR_FILENO, "pwd: error retrieving current directory: ");
		ft_mprintf(STDERR_FILENO, "getcwd: cannot access parent directories: ");
		ft_mprintf(STDOUT_FILENO, "No such file or directory\n");
	}
	else
		ft_mprintf(STDOUT_FILENO, "%s\n", getcwd(pwd, sizeof(pwd)));
}
