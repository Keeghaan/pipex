/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:21:13 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/08 16:37:15 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	split_path(char *av, t_cmd *cmd, int n)
{
	char	**split;

	if (ft_strlen(av) > 0)
	{
		split = ft_split(av, ' ');
		if (!split)
			return (1);
		if (ft_strchr(split[0], '/'))
		{
			if (access(split[0], F_OK | R_OK | X_OK) == 0)
				return (free_file(split), 0);
			if (ft_strchr(split[0], '/'))
			{
				if (cmd->in < 0 && n == 2 + cmd->here_doc)
					return (free_file(split), 2);
				ft_printf("%s: %s: %s\n", SH, split[0], strerror(errno));
				return (free_file(split), 2);
			}
		}
		free_file(split);
		return (4);
	}
	return (3);
}

static void	check_path_cmd(int ac, t_cmd *cmd, char **av)
{
	int		n;

	if (!cmd->env[0])
	{
		n = 1 + cmd->here_doc;
		while (++n < ac -1)
		{
			if (cmd->in < 0 && n == 2 + cmd->here_doc)
				n++;
			split_path(av[n], cmd, n);
			no_env2(av, cmd, n);
		}
	}
	else
	{
		n = ac - 1;
		while (--n >= 2 + cmd->here_doc)
			split_path(av[n], cmd, n);
	}
}

static int	no_env(int ac, t_cmd *cmd, char **av, int n)
{
	int	err;

	n = 2 + cmd->here_doc;
	if (!(cmd->in < 0 && n == 2 + cmd->here_doc))
		err = check_cmd(n, av[n], cmd);
	n = ac - 1;
	while (--n >= 3 + cmd->here_doc)
		err = check_cmd(n, av[n], cmd);
	return (err);
}

static int	with_env(int ac, t_cmd *cmd, char **av, int n)
{
	int	err;

	n = ac - 1;
	while (--n >= 2 + cmd->here_doc)
	{
		if (cmd->in < 0 && n == 2 + cmd->here_doc)
			n--;
		err = check_cmd(n, av[n], cmd);
	}
	return (err);
}

int	check_args(int ac, char **av, t_cmd *cmd)
{
	int	n;
	int	err;
	int	both;

	err = 0;
	n = 0;
	check_path_cmd(ac, cmd, av);
	both = check_cmd(1, av[ac - 2], cmd);
	if (!cmd->env[0])
		err = no_env(ac, cmd, av, n);
	else
		err = with_env(ac, cmd, av, n);
	if ((err && both) || both)
	{
		if (cmd->here_doc)
			unlink(".here_doc");
		return (free_file(cmd->env), 127);
	}
	return (0);
}
