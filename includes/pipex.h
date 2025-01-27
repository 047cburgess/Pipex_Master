#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_pipe
{
	int	pipe_fd[2];
	int	in_fd;
	int	out_fd;
	pid_t	pid1;
	pid_t	pid2;
	char	**args;
	char	*paths;
	char	**split_paths;
	char	*path;
}	t_pipe;

// PIPE.C
void	set_up_pipe(int *pipe_fd);
void	ft_free(char **var);
void	execute_command(t_pipe *pipe, char *cmd, char **envp);
void	init_struct(t_pipe *data);


// CLEAN UP SHIT
void	clean_up(t_pipe *data);
void	free_split(char **array);
void	close_pipe(t_pipe *data);

#endif
