/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 10:30:27 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/01 10:36:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	pwd_builtin(void)
{
	char	pwd[PATH_MAX];

	ft_mprintf(STDOUT_FILENO, "%s\n", getcwd(pwd, sizeof(pwd)));
}
