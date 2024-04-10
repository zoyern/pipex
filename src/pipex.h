/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:30 by marvin            #+#    #+#             */
/*   Updated: 2024/04/10 19:21:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <type.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <utils.h>
# include <memory.h>
# include <pipe.h>
# include <fork.h>
# include <exec.h>
# include <string.h>

typedef struct s_sofork_pid
{
	int	parent;
	int child;

}	t_sofork_pid;

typedef struct s_sopipe
{
	int	read;
	int write;

}	t_sopipe;

typedef struct s_sopipe_get
{
	int				(*message)(int fd, void *data, size_t size); 
	int				(*integer)(int fd); 
	char			*(*string)(t_solib *solib, int fd);
	char			**(*strings)(t_solib *solib, int fd); 
	char			*(*file)(t_solib *solib, int fd, int size); 
}	t_sopipe_get;

typedef struct s_sopipe_send
{
	int				(*message)(int fd, void *data, size_t size); 
	int				(*integer)(int fd, int data); 
	int				(*string)(int fd, char *data);
	int				(*strings)(int fd, char **data); 
}	t_sopipe_send;

typedef struct s_sofork_pipes
{
	t_sopipe *parent;
	t_sopipe *child;
}	t_sofork_pipes;

// 1 ecriture
// 0 lecture


//read_data_from_pipe(pipefd_parent_to_child[0], &received_num, sizeof(int));
//write_data_to_pipe(pipefd_child_to_parent[1], response, strlen(response) + 1);

typedef struct s_sofork_child{

	t_sofork_pid	*pid;
	t_sofork_pipes	*pipes;
	t_sopipe		*this;
	t_sopipe_send	*send;
	t_sopipe_get	*get;
}	t_sofork_child;

typedef struct s_sofork_parent{
	t_sofork_pid	*pid;
	t_sofork_pipes	*pipes;
	t_sopipe		*this;
	t_sopipe_send	*send;
	t_sopipe_get	*get;

	int				status;
	void			(*wait)(t_sofork_parent *parent, int unlock, int close);
	void			(*close)(t_sofork_parent *parent);
	

}	t_sofork_parent;

typedef struct s_solib_memory {
	void			*ptr;
	t_solib_memory	*next;
}	t_solib_memory;

typedef struct s_solib_new
{
	t_sofork_parent	*(*fork)(t_solib *solib, int (*callback)(t_solib *solib, t_sofork_child *));
	t_sopipe	*(*pipe)(t_solib *solib);
	t_sopipe	*(*pipe_data)(t_solib *solib, int pipe_read, int pipe_write);
} t_solib_new;

typedef struct s_solib_cmd
{
	char	*name;
	int		argc;
	char	**argv;
	char	**envp;
} t_solib_cmd;

typedef struct s_solib_file
{
	int				(*open)(t_solib *solib, int state);
	int				(*read)(t_solib *solib, int state);
	int				(*close)(t_solib *solib, int state);
} t_solib_file;

typedef struct s_solib{
	t_solib_cmd		*cmd;
	t_solib_memory	*memory;
	t_solib_new		*new;
	t_solib_file	file;
	int				(*close)(t_solib *solib, int state);
	char			*(*shell)(t_solib *solib, char *command);
	int				(*exec)(t_solib *solib, char *command, int read, int write);
	void			(*pipex)(t_solib *solib, int in, int out, char **commands);
	char			*(*pipexfd)(t_solib *solib, int in, int out, char **commands);
	void			*(*malloc)(t_solib *solib, unsigned long size);
	t_bool			(*free)(t_solib *solib, void *ptr);
	int				(*open)(char *path, int flags);
	char			*(*read_file)(t_solib *solib,  int fd, int size);
}	t_solib;

#endif