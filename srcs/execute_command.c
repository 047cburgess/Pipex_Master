/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:48:18 by caburges          #+#    #+#             */
/*   Updated: 2025/01/27 16:31:01 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_command(t_pipe *data, char *cmd);
char	*get_paths(char **envp);
void	find_executable(t_pipe *data, char *cmd, char **envp);

void	execute_command(t_pipe *data, char *cmd, char **envp)
{
	parse_command(data, cmd);
	data->paths = get_paths(envp);
	data->split_paths = ft_split(data->paths, ':');
	if (data->args && data->args && envp)
		find_executable(data, data->args[0], data->split_paths);
	if (data->path && data->args && envp)
		execve(data->path, data->args, envp);
	clean_up(data);
	exit(EXIT_FAILURE);
}

void	find_executable(t_pipe *data, char *cmd, char **paths)
{
	char	*new_cmd;
	char	*test;

	if (paths != NULL)
	{	
		new_cmd = ft_strjoin("/", cmd);
		while (*paths != NULL)
		{
			test = ft_strjoin(*paths, new_cmd);
			if (access(test, X_OK) == 0)
			{
				ft_free(&new_cmd);
				data->path = test;
				data->args[0] = test;
				return ;
			}
			ft_free(&test);
			paths++;
		}
		ft_free(&new_cmd);
		ft_free(&test);
	}
	data->path = cmd;
}

void	parse_command(t_pipe *data, char *cmd)
{
	data->args = ft_split(cmd, ' ');
}

char	*get_paths(char **envp)
{
	if (envp)
	{
		while (*envp != NULL)
		{
			if (ft_strncmp("PATH=", *envp, 5) == 0)
				return (*envp + 5);
			envp++;
		}
	}
	return (NULL);
}
