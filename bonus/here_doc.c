/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:50:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/06/30 15:42:47 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	get_heredoc(int fd, char *limiter)
{
	char	*tmp;

	while (1)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (!tmp)
			break ;
		write(fd, tmp, ft_strlen(tmp));
		if (!ft_strncmp(limiter, tmp, ft_strlen(limiter))
			&& ft_strlen(limiter) == ft_strlen(tmp) - 1)
			break ;
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
