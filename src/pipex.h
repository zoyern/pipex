/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:30 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 04:56:02 by marvin           ###   ########.fr       */
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
# include <fork.h>
# include <string.h>

typedef struct s_sofork_pid
{
	int	parent;
	int child;

}	t_sofork_pid;

typedef struct s_sofork_pipe
{
	int	read;
	int write;

}	t_sofork_pipe;

typedef struct s_sofork_pipes
{
	t_sofork_pipe *parent;
	t_sofork_pipe *child;
}	t_sofork_pipes;

// 1 ecriture
// 0 lecture


//read_data_from_pipe(pipefd_parent_to_child[0], &received_num, sizeof(int));
//write_data_to_pipe(pipefd_child_to_parent[1], response, strlen(response) + 1);

typedef struct s_sofork_child{

	t_sofork_pid	*pid;
	t_sofork_pipes	*pipes;
	t_sofork_pipe	*this;
	//						child->send(child->parent->write, void *data, sizeof(var));
	int				(*send)(int fd, void *data, size_t size); //fonction pour envoyer de l'enfant au parent
	int				(*get)(int fd, void *data, size_t size); //fonction pour recevoir du parent a l'enfant
}	t_sofork_child;

typedef struct s_sofork_parent{
	t_sofork_pid	*pid;
	t_sofork_pipes	*pipes;
	t_sofork_pipe	*this;

	int				(*send)(int fd, void *data, size_t size); //fonction pour envoyer du parent a l'enfant
	int				(*get)(int fd, void *data, size_t size); //fonction pour recevoir de l'enfant au parent
}	t_sofork_parent;

typedef struct s_solib_memory {
	void			*ptr;
	t_solib_memory	*next;
}	t_solib_memory;

typedef struct s_solib_new
{
	t_sofork_parent	*(*fork)(t_solib *solib, int (*callback)(t_solib *solib, t_sofork_child *));
} t_solib_new;

typedef struct s_solib{
	t_solib_memory	*memory;
	t_solib_new		*new;
	int				(*close)(t_solib *solib, int state);
	void			*(*malloc)(t_solib *solib, int size);
	t_bool			(*free)(t_solib *solib, void *ptr);
}	t_solib;

#endif