/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:24:40 by caburges          #+#    #+#             */
/*   Updated: 2025/01/27 14:57:40 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipe *data)
{
	data->args = NULL;
	data->paths = NULL;
	data->split_paths = NULL;
	data->path = NULL;
}
