/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:09 by marvin            #+#    #+#             */
/*   Updated: 2024/04/18 11:08:45 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int write_data_to_pipe(int fd, void *data, size_t size)
{
    if (write(fd, data, size) == -1)
	{
        return (perror("pipex: write"), 1);
	}
	return (0);
}

// Fonction pour lire des données depuis un pipe
int read_data_from_pipe(int fd, void *data, size_t size)
{
    if (read(fd, data, size) == -1)
	{
        return (perror("pipex: read"), 1);
	}
    return (0);
}

// 1 ecriture
// 0 lecture

t_sopipe	*new_pipe(t_solib *solib)
{
	int pipefd[2];
	t_sopipe	*new_pipe;

	new_pipe = (t_sopipe *)solib->malloc(solib, sizeof(t_sopipe));
	if (pipe(pipefd) == -1)
        solib->close(solib, EXIT_FAILURE);
	new_pipe->read = pipefd[0];
	new_pipe->write = pipefd[1];
	return (new_pipe);
}

t_sopipe	*new_pipe_data(t_solib *solib, int pipe_read, int pipe_write)
{
	t_sopipe	*new_pipe;

	new_pipe = (t_sopipe *)solib->malloc(solib, sizeof(t_sopipe));
	if (pipe_read < 0 || pipe_write < 0)
        solib->close(solib, EXIT_FAILURE);
	new_pipe->read = pipe_read;
	new_pipe->write = pipe_write;
	return (new_pipe);
}