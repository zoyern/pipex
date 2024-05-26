/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <pipex.h>

t_sopipe	*new_pipe(t_solib *solib);
t_sopipe	*new_pipe_data(t_solib *solib, int pipe_read, int pipe_write);
int			write_data_to_pipe(int fd, void *data, size_t size);
int			read_data_from_pipe(int fd, void *data, size_t size);

#endif
