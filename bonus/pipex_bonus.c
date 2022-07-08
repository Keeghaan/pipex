/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:11:23 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/08 15:06:25 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_pipe(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->no - 1)
	{
		cmd->fd[i] = malloc(sizeof(int) * 2);
		if (pipe(cmd->fd[i]) == -1)
		{
			ft_printf("%s\n", strerror(errno));
			close_pipes(cmd);
			free_parent(cmd);
			exit(1);
		}
	}
}

static int	init_struct(t_cmd *cmd, int ac, char **en, char **av)
{
	int	i;

	i = -1;
	cmd->in = -3;
	cmd->out = -4;
	cmd->std_in = 0;
	cmd->env_i = 1;
	if (ac < check_heredoc(av, cmd))
	{
		if (cmd->here_doc)
			unlink(".here_doc");
		return (ft_printf("Too few arguments\n"), -1);
	}
	cmd->no = (ac - 3 - cmd->here_doc);
	cmd->pid = malloc(sizeof(pid_t) * cmd->no);
	while (++i < cmd->no)
		cmd->pid[i] = -2;
	if (get_env(cmd, en))
		return (free(cmd->pid), -2);
	return (0);
}

static int	ft_open(int ac, char **av, t_cmd *cmd, char **en)
{
	if (init_struct(cmd, ac, en, av) < 0)
		return (-1);
	if (cmd->here_doc)
	{
		if (here_doc(av[2], cmd))
			return (free_file(cmd->env), unlink(".here_doc"), -2);
		cmd->out = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		return (0);
	}
	else
	{
		cmd->in = open(av[1], O_RDONLY);
		if (cmd->in < 0)
			ft_printf("%s: %s: %s\n", SH, av[1], strerror(errno));
		cmd->out = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (cmd->out < 0)
			return (0);
	}
	if (check_args(ac, av, cmd) == 127)
		return (close_files(cmd), 127);
	return (0);
}

static int	pipex(char **av, char **en, t_cmd cmd)
{
	int	n;
	int	i;

	n = -1;
	i = -1;
	ft_pipe(&cmd);
	while (++n < cmd.no)
	{
		if (cmd.in < 0 && n == 0)
			n++;
		if (child_process(n, av, en, &cmd))
			return (1);
	}
	close_files(&cmd);
	close_pipes(&cmd);
	while (++i < cmd.no)
		waitpid(cmd.pid[i], NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **en)
{
	t_cmd	cmd;
	int		err;

	err = ft_open(ac, av, &cmd, en);
	if (err < 0)
		return (close_fileno(), 0);
	if (err == 127)
		return (free(cmd.pid), close_fileno(), 127);
	cmd.fd = malloc(sizeof(int *) * (cmd.no - 1));
	if (!cmd.fd)
		return (free_file(cmd.env), close_fileno());
	if (pipex(av, en, cmd))
		return (close_pipes(&cmd), free_parent(&cmd)
			, close_fileno());
	return (free_parent(&cmd), 0);
}
