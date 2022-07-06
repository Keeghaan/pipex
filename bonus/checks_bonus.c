/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:21:13 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/06 12:17:29 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_digit(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_cmd(int n, char *av, t_cmd *cmd)
{
	if (ft_strlen(av) > 0)
	{
		cmd->cmd = ft_split(av, ' ');
		if (!cmd->cmd)
			return (2);
		if (n == 1)
			cmd->path = get_path(cmd->cmd[0], cmd->env, 0, n);
		else
			cmd->path = get_path(cmd->cmd[0], cmd->env, 1, n);
		if (!cmd->path)
			return (free_file(cmd->cmd), 4);
		free(cmd->path);
		free_file(cmd->cmd);
		return (0);
	}
	return (0);
}

static int	split_path(char *av, int err)
{
	char	**split;

	if (ft_strlen(av) > 0)
	{
		split = ft_split(av, ' ');
		if (!split)
		{
			err++;
			return (1);
		}
		if (ft_strchr(split[0], '/'))
		{
			if (access(split[0], F_OK | X_OK) == 0)
				return (free_file(split), 0);
			err++;
			return (free_file(split), 2);
		}
		free_file(split);
		err++;
		return (4);
	}
	err++;
	return (3);
}

static int	check_path_cmd(int ac, int here_doc, char **av, char **en)
{
	int		n;
	int		err;

	n = ac - 1;
	err = 0;
	if (ft_strlen(av[2 + here_doc]) < 1 && !en[0])
	{
		ft_printf("env: ‘’: %s\n", strerror(2));
		err++;
	}
	while (2 + here_doc <= n)
	{
		if (ft_strlen(av[n]) < 1)
		{
			if (!en[0] && n == 2 + here_doc)
				break ;
			ft_printf("Command '' not found\n");
			err++;
		}
		else
			split_path(av[n], err);
		n--;
	}
	if (!err)
		return (0);
	return (2);
}

int	check_args(int ac, char **av, t_cmd *cmd)
{
	int	n;
	int	err;
	int	both;

	n = ac - 2;
	err = 0;
	check_path_cmd(ac, cmd->here_doc, av, cmd->env);
	both = check_cmd(1, av[ac - 2], cmd);
	while (2 + cmd->here_doc <= n)
	{
		if (cmd->in < 0 && n == 2 + cmd->here_doc)
			break ;
		err = check_cmd(n, av[n], cmd);
		n--;
	}
	if ((err && both) || both)
	{
		if (cmd->here_doc)
			unlink(".here_doc");
		return (free_file(cmd->env), 127);
	}
	return (0);
}
