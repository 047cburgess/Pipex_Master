#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_pipe
{
	int	pipe_fd[2];
	int	in_fd;
	int	out_fd;
	pid_t	pid1;
	pid_t	pid2;
	char	**args;
	char	*paths;
	char	*full_path;
}	t_pipe;

// PIPE.C
void	set_up_pipe(t_pipe *pipe);

#endif