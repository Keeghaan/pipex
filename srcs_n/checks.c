/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:17:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/07 15:20:08 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	path_not_found(int found, t_cmd *cmd)
{
	if (!found)
	{
		cmd->env = malloc(sizeof(char *));
		cmd->env[0] = NULL;
		return (1);
	}
	return (0);
}

int	check_cmd(int n, char *av, t_cmd *cmd)
{
	if (ft_strlen(av) < 1)
		return (0);
	cmd->cmd = ft_split(av, ' ');
	if (!cmd->cmd)
		return (1);
	if (n == 1)
		cmd->path = get_path(cmd->cmd[0], cmd, 0, n);
	else
		cmd->path = get_path(cmd->cmd[0], cmd, 1, n);
	if (!cmd->path && cmd->env[0])
		return (free_file(cmd->cmd), 5);
	free(cmd->path);
	free_file(cmd->cmd);
	return (0);
}

int	check_path_cmd(int i, char *cmd, t_cmd *command)
{
	char	**split;

	if (ft_strlen(cmd) < 1)
	{
		if (!command->env[0] && i == 2 && !command->env_i)
			return (ft_printf("env: ‘’: %s\n", strerror(2)), 0);
		else if (!command->env[0] && command->env_i)
			return (ft_printf("%s: : %s\n", SH, strerror(2), 0));
		else if (command->env[0] || (!command->env[0] && !command->env_i))
			return (ft_printf("Command '' not found\n"), 0);
	}
	else
	{
		split = ft_split(cmd, ' ');
		if (!split)
			return (3);
		if (ft_strchr(split[0], '/'))
		{
			if (access(split[0], F_OK | X_OK) == 0)
				return (free_file(split), 0);
			return (free_file(split), 1);
		}
		return (free_file(split), 2);
	}
	return (1);
}

int	other_check(int ac, char **av, t_cmd *cmd)
{
	int	check;
	int	i;

	check = 0;
	if (!cmd->env[0])
		i = 2;
	else
		i = 3;
	if (ac != 5)
	{
		ft_printf("<./pipex infile cmd1 cmd2 outfile>\n");
		return (1);
	}
	if (check_path_cmd(i, av[i], cmd))
		check = 1;
	if (!cmd->env[0])
		i++;
	else
		i--;
	if (check_path_cmd(i, av[i], cmd) || check)
		return (1);
	return (0);
}

int	check_args(int ac, char **av, t_cmd *cmd)
{
	int	n;
	int	err;
	int	both;

	n = ac - 2;
	other_check(ac, av, cmd);
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
