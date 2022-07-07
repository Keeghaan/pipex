/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:26:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/07 17:34:12 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	check_digit(char *cmd)
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

static void	msg_error(int infile, int msg, int n, char *cmd)
{
	int	digit;

	digit = check_digit(cmd);
	if (msg && n > 1 && !ft_strchr(cmd, '/'))
	{
		if (infile < 0 && n == 2)
			return ;
		if (!digit)
			ft_printf("Command '%s' not found\n", cmd);
		else
			ft_printf("%s: command not found\n", cmd);
	}
}

static int	ft_more_test(int n, t_cmd *command, char *cmd, int msg)
{
	if (msg && ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (0);
		ft_printf("%s: %s: %s\n", SH, cmd, strerror(errno));
	}
	else if (!command->env[0] && msg && !command->env_i)
	{
		if (command->in > -1 && n == 2)
			return (ft_printf("env: ‘%s’: %s\n", cmd, strerror(2)));
		else if (command->in < 0 && n == 2)
			return (1);
		else
			return (ft_printf("Command '%s' not found\n", cmd), 1);
	}
	else if (!command->env[0] && msg && command->env_i)
		return (ft_printf("%s: %s: %s\n", SH, cmd, strerror(2)), 1);
	if (!ft_strncmp(cmd, "df", ft_strlen(cmd)))
	{
		if (msg)
			ft_printf("%s: %s: %s\n", cmd, DF, strerror(1));
		return (2);
	}
	return (0);
}

static char	*ret_path(int i, char *cmd, t_cmd *command)
{
	char	*cmd_path;
	char	*tmp;

	tmp = NULL;
	cmd_path = NULL;
	if (!check_path_cmd(0, cmd, command))
		cmd_path = ft_strdup(cmd);
	else
	{
		tmp = ft_strjoin(command->env[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*get_path(char *cmd, t_cmd *command, int msg, int n)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	i = 0;
	if (command->in > -1 || (command->in < 0 && n != 2))
	{
		if (ft_more_test(n, command, cmd, msg))
			return (NULL);
	}
	while (command->env[i])
	{
		cmd_path = ret_path(i, cmd, command);
		if (cmd_path != NULL)
			return (cmd_path);
		i++;
	}
	if (command->env[0])
		msg_error(command->in, msg, n, cmd);
	return (cmd_path);
}
