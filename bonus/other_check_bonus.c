/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:03:21 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/08 16:21:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	no_env2(char **av, t_cmd *cmd, int n)
{
	if (ft_strlen(av[n]) < 1 && n == 2 + cmd->here_doc
		&& !cmd->env_i && cmd->in > -1)
		ft_printf("env: ‘’: %s\n", strerror(2));
	else if (cmd->env_i && ft_strlen(av[n]) < 1
		&& n != 2 + cmd->here_doc)
		ft_printf("%s: : %s\n", SH, strerror(2));
	else if (!cmd->env_i && ft_strlen(av[n]) < 1
		&& n != 2 + cmd->here_doc)
		ft_printf("Command '' not found\n");
	else if (ft_strlen(av[n]) > 0 && n == 2 + cmd->here_doc
		&& !cmd->env_i && cmd->in > -1)
		ft_printf("env: ‘%s’: %s\n", av[n], strerror(2));
	else if (cmd->env_i && !ft_strchr(av[n], '/'))
		ft_printf("%s: %s: %s\n", SH, av[n], strerror(2));
}
