/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:17:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/01 16:27:37 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	path_not_found(int found, t_cmd *cmd)
{
	if (!found)
	{
		cmd->env[0] = NULL;
		return (1);
	}
	return (0);
}

int	check_cmd(int n, char *av, t_cmd *cmd)
{
	if (ft_strlen(av) < 1)
		return (ft_printf("Command '' not found\n"), 1);
	cmd->cmd = ft_split(av, ' ');
	if (!cmd->cmd)
		return (1);
	cmd->path = get_path(cmd->cmd[0], cmd->env, 1, n);
	if (!cmd->path && cmd->env[0])
	{
		if (cmd->in < 0 && n == 2)
			return (free_file(cmd->cmd), 4);
		else
		{
			ft_printf("%s: %s\n", SH, cmd->cmd[0], CMDERR);
			return (free_file(cmd->cmd), 5);
		}
	}
	free(cmd->path);
	free_file(cmd->cmd);
	return (0);
}

int	check_path_cmd(char *cmd, int msg)
{
	int	digit;
	int	i;

	digit = 0;
	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, 0) == 0)
			return (0);
		while (cmd[i] && msg)
		{
			if (ft_isdigit(cmd[i]))
				digit = 1;
			i++;
		}
		if (digit)
			ft_printf("%s: %s\n", cmd, CMDERR);
		else
			ft_printf("Command '%s' not found\n", cmd);
		return (1);
	}
	return (2);
}

int	check_args(int ac, char **av, t_cmd *cmd)
{
	int	n;
	int	err;
	int	both;

	n = ac - 2;
	both = 0;
	if (ac != 5)
	{
		ft_printf("<./pipex infile cmd1 cmd2 outfile>\n");
		return (free_file(cmd->env), 1);
	}
	if (check_path_cmd(av[2], 1) || check_path_cmd(av[3], 1))
		return (0);
	both = check_cmd(1, av[ac - 2], cmd);
	while (n > 1)
	{
		err = check_cmd(n, av[n], cmd);
		n--;
	}
	if ((err && both) || both)
		return (free_file(cmd->env), 127);
	return (0);
}
