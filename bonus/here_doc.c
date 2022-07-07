/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:50:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/07 15:32:28 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	more_test(char **en, char *cmd, int msg, int env_i)
{
	if (!en[0] && msg)
	{
		if (env_i && !ft_strncmp(cmd, "/dev/stdout", ft_strlen(cmd)))
			return (ft_printf("%s: %s: %s\n", SH, cmd, strerror(26)), 1);
		else if ((!ft_strncmp(cmd, "/dev/stdin", ft_strlen(cmd)))
			|| (!ft_strncmp(cmd, "/dev/stdout", ft_strlen(cmd))))
			return (ft_printf("%s: %s: %s\n", SH, cmd, strerror(13)), 1);
		else if (env_i)
			return (ft_printf("%s: %s: %s\n", SH, cmd, strerror(2)), 1);
		else
			return (ft_printf("%s: %s: %s\n", SH, cmd, strerror(2)), 1);
	}
	if (!ft_strncmp(cmd, "df", ft_strlen(cmd)))
	{
		if (msg)
			ft_printf("%s: %s: %s\n", cmd, DF, strerror(1));
		return (1);
	}
	return (0);
}

int	check_heredoc(char **av, t_cmd *cmd)
{
	if (!ft_strncmp("here_doc", av[1], ft_strlen("here_doc") + 1))
	{
		cmd->here_doc = 1;
		return (6);
	}
	else
	{
		cmd->here_doc = 0;
		return (5);
	}
}

static void	get_heredoc(int fd, char *limiter)
{
	char	*tmp;

	while (1)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (!tmp)
			break ;
		if (!ft_strncmp(limiter, tmp, ft_strlen(limiter))
			&& ft_strlen(limiter) == ft_strlen(tmp) - 1)
			break ;
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	return ;
}

int	here_doc(char *limiter, t_cmd *cmd)
{
	int		fd;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close_files(cmd), 1);
	get_heredoc(fd, limiter);
	close(fd);
	get_next_line(-1);
	close_files(cmd);
	cmd->in = open(".here_doc", O_RDONLY);
	if (cmd->in == -1)
		return (unlink(".here_doc"), 3);
	return (0);
}
