/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:20:31 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 16:02:12 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//solls auch mit 1 cmd funcktionieren?
int	check_if_here_doc(int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac == 6)
			return (1);
		else
			exit(0);
	}
	return (0);
}

int	here_doc(t_data *data)
{
	char	*line;

	data->here_doc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->here_doc == -1)
		cleanup(data);
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(data->here_doc, line, ft_strlen(line));
		free(line);
	}
	close(data->here_doc);
	data->here_doc = open(HERE_DOC, O_RDONLY);
	if (data->here_doc < 0)
		unlink(".heredoc_tmp");
	return (0);
}
