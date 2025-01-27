/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:38:48 by caburges          #+#    #+#             */
/*   Updated: 2025/01/27 15:43:41 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	free_split(char **array);
void	close_pipe(t_pipe *data);

void	clean_up(t_pipe *data)
{
	close_pipe(data);
	ft_putendl_fd("cleaned up close pipe", 2);
	free_split(data->args);
	ft_putendl_fd("cleaned up args split", 2);
	free_split(data->split_paths);
	ft_putendl_fd("cleaned up paths split", 2);
	ft_free(&data->path);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	close_pipe(t_pipe *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}
