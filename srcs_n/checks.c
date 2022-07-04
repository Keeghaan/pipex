/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:17:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/04 14:17:46 by jcourtoi         ###   ########.fr       */
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
	if (n == 1)
		cmd->path = get_path(cmd->cmd[0], cmd->env, 0, n);
	else
		cmd->path = get_path(cmd->cmd[0], cmd->env, 1, n);
	if (!cmd->path && cmd->env[0])
	{
		if (cmd->in < 0 && n == 2)
			return (free_file(cmd->cmd), 4);
		else
		{
			ft_printf("%s: %s: %s\n", SH, cmd->cmd[0], CMDERR);
			return (free_file(cmd->cmd), 5);
		}
	}
	free(cmd->path);
	free_file(cmd->cmd);
	return (0);
}

int	check_path_cmd(char *cmd, int msg)
{
	char	**split;

	split = ft_split(cmd, ' ');
	if (!split)
		return (3);
	if (ft_strchr(split[0], '/'))
	{
		if (access(split[0], 0) == 0)
			return (free_file(split), 0);
		if (msg)
			ft_printf("%s: %s: %s\n", SH, split[0], strerror(errno));
		return (free_file(split), 1);
	}
	return (free_file(split), 2);
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
		return (1);
	}
	if (check_path_cmd(av[3], 1) != 2)
		both = 1;
	if (check_path_cmd(av[2], 1) != 2 || both)
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
