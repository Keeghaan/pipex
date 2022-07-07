/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:08:00 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/07 16:29:03 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	empty_cmd(t_cmd *command, int i)
{	
	if (!command->env[0] && i == 2 && !command->env_i && command->in > -1)
		ft_printf("env: ‘’: %s\n", strerror(2));
	else if (!command->env[0] && command->env_i)
	{
		if (command->in < 0 && i == 2)
			return ;
		ft_printf("%s: : %s\n", SH, strerror(2));
	}
	else if (command->env[0] || (!command->env[0] && !command->env_i))
	{
		if (command->in < 0 && i == 2)
			return ;
		ft_printf("Command '' not found\n");
	}
}

int	check_path_cmd(int i, char *cmd, t_cmd *command)
{
	char	**split;

	if (ft_strlen(cmd) < 1)
		return (empty_cmd(command, i), 1);
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
