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

t_sofork_pipes	*new_pipes(t_solib *solib)
{
	t_sofork_pipes	*new_pipes;
	t_sopipe	*parent_pipe;
	t_sopipe	*child_pipe;

	parent_pipe = solib->new->pipe(solib);
	if (!parent_pipe)
		return(perror("pipex: pipe"), NULL);
	child_pipe = solib->new->pipe(solib);
	if (!parent_pipe)
		return(perror("pipex: pipe"), close(parent_pipe->read), close(parent_pipe->write), NULL);

	new_pipes = (t_sofork_pipes *)solib->malloc(solib, sizeof(t_sofork_pipes));
	if (parent_pipe->read < 0 || parent_pipe->write < 0 || child_pipe->read < 0 || child_pipe->write < 0)
        solib->close(solib, EXIT_FAILURE);
	new_pipes->parent = parent_pipe;
	new_pipes->child = child_pipe;
	return (new_pipes);
}

int	new_sofork_pipes(t_solib *solib, t_sofork_parent *parent, t_sofork_child *child)
{
	t_sofork_pipes	*pipes;
	
	pipes = new_pipes(solib);
	parent->pipes = pipes;
	child->pipes = pipes;
	parent->this = solib->new->pipe_data(solib, pipes->child->read, pipes->parent->write);
	child->this = solib->new->pipe_data(solib, pipes->parent->read, pipes->child->write);
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

t_sopipe_send	*sofork_send_init(t_solib *solib)
{
	t_sopipe_send	*send;

	send = solib->malloc(solib, sizeof(t_sopipe_send));
	send->message = write_data_to_pipe;
	send->integer = sofork_send_int;
	send->string = sofork_send_string;
	send->strings = sofork_send_strings;
	return (send);
}

t_sopipe_get	*sofork_get_init(t_solib *solib)
{
	t_sopipe_get	*get;

	get = solib->malloc(solib, sizeof(t_sopipe_get));
	get->message = read_data_from_pipe;
	get->integer = sofork_read_int;
	get->string = sofork_read_string;
	get->strings = sofork_read_strings;
	get->file = sofork_read_file;
	return (get);
}


t_sofork_parent	*new_fork(t_solib *solib, int (*callback)(t_solib *solib, t_sofork_child *))
{
	t_sofork_parent	*parent;
	t_sofork_child	*child;
	t_sopipe_send	*send;
	t_sopipe_get	*get;

	parent = (t_sofork_parent *)solib->malloc(solib, sizeof(t_sofork_parent));
	child = (t_sofork_child *)solib->malloc(solib, sizeof(t_sofork_child));

	if (new_sofork_pipes(solib, parent, child))
		exit(EXIT_FAILURE);
	send = sofork_send_init(solib);
	get = sofork_get_init(solib);
	parent->send = send;
	parent->get = get;
	child->send = send;
	child->get = get;
	if (new_sofork_fork(solib, parent, child, callback))
		exit(EXIT_FAILURE);
	return (parent);
}
