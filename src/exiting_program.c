/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:37:55 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 14:27:18 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>

void	free_2d_arr(char **path)
{
	int	i;

	i = 0;
	if (path == NULL)
		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	path = NULL;
}

//ft_printf("Pipe read\n");
//ft_printf("Pipe write\n");
//ft_printf("Cleaning up\n");
void	cleanup(t_data *data)
{
	if (errno != 0)
		perror("My error message");
	if (data->pids != NULL)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->path != NULL)
	{
		free_2d_arr(data->path);
		data->path = NULL;
	}
	if (data->pipe[0] != -1)
	{
		close(data->pipe[0]);
		data->pipe[0] = -1;
	}
	if (data->pipe[1] != -1)
	{
		close(data->pipe[1]);
		data->pipe[1] = -1;
	}
	exit(0);
}
