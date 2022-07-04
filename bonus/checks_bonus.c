/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:21:13 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/04 12:52:55 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_files(t_cmd *cmd)
{
	if (cmd->in > -1)
		close(cmd->in);
	if (cmd->out > -1)
		close(cmd->out);
}

void	close_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->no - 1)
	{
		close(cmd->fd[i][0]);
		close(cmd->fd[i][1]);
		i++;
	}
}

int	check_cmd(int n, char *av, t_cmd *cmd)
{
	if (ft_strlen(av) < 1)
		return (ft_printf("Command '' not found\n"), 1);
	cmd->cmd = ft_split(av, ' ');
	if (!cmd->cmd)
		return (2);
	cmd->path = get_path(cmd->cmd[0], cmd->env, 1, n);
	if (!cmd->path)
	{
		if (cmd->in < 0 && n == 2)
			return (free_file(cmd->cmd), 4);
		else
			return (free_file(cmd->cmd), 5);
	}
	free(cmd->path);
	free_file(cmd->cmd);
	return (0);
}

static int	check_path_cmd(int ac, int here_doc, char **av)
{
	int	n;
	int	err;

	n = ac - 2;
	err = 0;
	while (2 + here_doc <= n)
	{
		if (ft_strchr(av[n], '/'))
		{
			if (access(av[n], 0) == 0)
				return (0);
			ft_printf("%s: %s: %s\n", SH, av[n], strerror(errno));
			err++;
		}
		n--;
	}
	if (err)
		return (1);
	return (2);
}

int	check_args(int ac, char **av, t_cmd *cmd)
{
	int	n;
	int	err;
	int	both;

	n = ac - 2;
	if (check_path_cmd(ac, cmd->here_doc, av) != 2)
		return (0);
	both = check_cmd(1, av[ac - 2], cmd);
	while (2 + cmd->here_doc < n)
	{
		if (cmd->in < 0 && n == 2)
			break ;
		err = check_cmd(n, av[n], cmd);
		n--;
	}
	if ((err && both) || both)
	{
		if (cmd->here_doc)
			unlink(".here_doc");
		return (127);
	}
	return (0);
}
