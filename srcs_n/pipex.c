/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:01:44 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/08 12:41:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_env(t_cmd *cmd, char **envp)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (!envp[i])
		cmd->env_i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp[i] = ft_strchr(envp[i], '/');
			found = 1;
			break ;
		}
		i++;
	}
	if (path_not_found(found, cmd))
		return (0);
	cmd->env = ft_split(envp[i], ':');
	if (!cmd->env)
		return (3);
	return (0);
}

int	ft_open(int ac, char **av, t_cmd *cmd, char **envp)
{
	int	err;

	cmd->in = -2;
	cmd->out = -2;
	cmd->env_i = 1;
	open_out(cmd, av);
	cmd->in = open(av[1], O_RDONLY);
	if (cmd->in == -1)
		ft_printf("%s: %s: %s\n", SH, av[1], strerror(errno));
	if (ft_strlen(av[1]) < 1 && ft_strlen(av[ac - 1]) < 1)
		return (close_parent(), -3);
	if (get_env(cmd, envp))
		return (-1);
	err = check_args(ac, av, cmd);
	if (err == 127)
		return (close_files(cmd), close_parent(), 127);
	return (0);
}

int	pipex(t_cmd cmd, char **av, char **envp)
{
	if (pipe(cmd.fd) < 0)
		return (free_file(cmd.env), 3);
	if ((cmd.in > -1))
	{
		cmd.pid1 = fork();
		if (cmd.pid1 < 0)
			return (close_files(&cmd), 4);
		if (cmd.pid1 == 0)
			child_process_one(&cmd, av, envp);
	}
	cmd.pid2 = fork();
	if (cmd.pid2 < 0)
		return (close_files(&cmd), 5);
	if (cmd.pid2 == 0)
		child_process_two(&cmd, av, envp);
	close_fd(&cmd);
	close_files(&cmd);
	if (cmd.in > -1)
		waitpid(cmd.pid1, NULL, 0);
	waitpid(cmd.pid2, NULL, 0);
	return (free_file(cmd.env), 0);
}

int	main(int ac, char **av, char **en)
{
	t_cmd	cmd;
	int		err;

	if (ac != 5)
	{
		ft_printf("5 args expected <./pipex infile cmd1 cmd2 outfile>\n");
		return (close_parent(), 1);
	}
	err = ft_open(ac, av, &cmd, en);
	if (err == 127)
		return (127);
	if (err < 0)
		return (2);
	if (pipex(cmd, av, en))
		return (3);
	return (close_parent(), 0);
}
