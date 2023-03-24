/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:19:53 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 10:59:56 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>
#include <fcntl.h>

//S Tier functions
int	s_fork(t_data *data)
{
	int	ret;

	ret = fork();
	if (ret == -1)
	{
		cleanup(data);
		exit(0);
	}
	return (ret);
}

int	s_close(int fd, t_data *data)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
	{
		cleanup(data);
		exit(0);
	}
	ret = -1;
	return (ret);
}
