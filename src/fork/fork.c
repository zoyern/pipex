/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:42:28 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 02:42:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int write_data_to_pipe2(int fd, void *data, size_t size)
{
    if (write(fd, data, size) == -1)
	{
        return (perror("pipex: write"), 1);
	}
	return (0);
}

// Fonction pour lire des données depuis un pipe
int read_data_from_pipe2(int fd, void *data, size_t size)
{
    if (read(fd, data, size) == -1)
	{
        return (perror("pipex: read"), 1);
	}
    return (0);
}

// 1 ecriture
// 0 lecture

t_sofork_pipe	*new_pipe(t_solib *solib)
{
	int pipefd[2];
	t_sofork_pipe	*new_pipe;

	new_pipe = (t_sofork_pipe *)solib->malloc(solib, sizeof(t_sofork_pipe));
	if (pipe(pipefd) == -1)
        solib->close(solib, EXIT_FAILURE);
	new_pipe->read = pipefd[0];
	new_pipe->write = pipefd[1];
	return (new_pipe);
}

t_sofork_pipes	*new_pipes(t_solib *solib, t_sofork_pipe *parent, t_sofork_pipe *child)
{
	t_sofork_pipes	*new_pipes;

	new_pipes = (t_sofork_pipes *)solib->malloc(solib, sizeof(t_sofork_pipes));
	if (parent->read < 0 || parent->write < 0 || child->read < 0 || child->write < 0)
        solib->close(solib, EXIT_FAILURE);
	new_pipes->parent = parent;
	new_pipes->child = child;
	return (new_pipes);
}

t_sofork_pipe	*new_pipe_data(t_solib *solib, int pipe_read, int pipe_write)
{
	t_sofork_pipe	*new_pipe;

	new_pipe = (t_sofork_pipe *)solib->malloc(solib, sizeof(t_sofork_pipe));
	if (pipe_read < 0 || pipe_write < 0)
        solib->close(solib, EXIT_FAILURE);
	new_pipe->read = pipe_read;
	new_pipe->write = pipe_write;
	return (new_pipe);
}

int	myChild(t_solib *solib, t_sofork_child *child)
{
	(void)solib;
	(void)child;
	return (false);
}

int	new_sofork_pipe(t_solib *solib, t_sofork_parent *parent, t_sofork_child *child)
{
	t_sofork_pipe *parent_pipe;
	t_sofork_pipe *child_pipe;

	parent_pipe = new_pipe(solib);
	if (!parent_pipe)
		return(perror("pipex: pipe"), 1);
	child_pipe = new_pipe(solib);
	if (!parent_pipe)
		return(perror("pipex: pipe"), close(parent_pipe->read), close(parent_pipe->write), 1);
	parent->pipes = new_pipes(solib, parent_pipe, child_pipe);
	child->pipes = new_pipes(solib, parent_pipe, child_pipe);
	parent->this = new_pipe_data(solib, child_pipe->read, parent_pipe->write);
	child->this = new_pipe_data(solib, parent_pipe->read, child_pipe->write);
	return (0);
}

void	close_pipe(int fd_read, int fd_write)
{
	close(fd_read); // Fermeture du descripteur de fichier en écriture du pipe parent vers enfant
	close(fd_write);
}

int	new_sofork_fork(t_solib *solib, t_sofork_parent *parent, t_sofork_child *child, int (*callback)(t_solib *solib, t_sofork_child *))
{
	pid_t pid;

	parent->pid = (t_sofork_pid *)solib->malloc(solib, sizeof(t_sofork_pid));
	child->pid = (t_sofork_pid *)solib->malloc(solib, sizeof(t_sofork_pid));

	pid = fork();
    if (pid == -1)
        solib->close(solib, EXIT_FAILURE);
	else if (pid == 0) // Processus enfant
	{
		close(child->pipes->child->read);
		close(child->pipes->parent->write); // Fermeture du descripteur de fichier en écriture du pipe parent vers enfant
		child->pid->parent = getppid();
        child->pid->child = getpid();
		if (callback(solib, child))
		{
			perror("pipex: children pid : ");
			close_pipe(child->this->read, child->this->write);
			solib->close(solib, EXIT_FAILURE);
		}
		close_pipe(child->this->read, child->this->write);
		exit(solib->close(solib, EXIT_SUCCESS));
	}
	else
	{
		close(child->pipes->parent->read); // Fermeture du descripteur de fichier en écriture du pipe parent vers enfant
		close(child->pipes->child->write);
		parent->pid->parent = getpid();
        parent->pid->child = pid;
	}
	return (0);
}


t_sofork_parent	*new_fork(t_solib *solib, int (*callback)(t_solib *solib, t_sofork_child *))
{
	t_sofork_parent *parent;
	t_sofork_child *child;

	parent = (t_sofork_parent *)solib->malloc(solib, sizeof(t_sofork_parent));
	child = (t_sofork_child *)solib->malloc(solib, sizeof(t_sofork_child));

	if (new_sofork_pipe(solib, parent, child))
		exit(EXIT_FAILURE);
	parent->send = write_data_to_pipe2; // fonction pour envoyer du parent a l'enfant
	parent->get = read_data_from_pipe2; // fonction pour recevoir de l'enfant au parent
	child->send = write_data_to_pipe2;
	child->get = read_data_from_pipe2;
	if (new_sofork_fork(solib, parent, child, callback))
		exit(EXIT_FAILURE);
	return (parent);
}
