/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:43:20 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 02:43:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <pipex.h>

t_sofork_parent	*new_fork(t_solib *solib, int (*callback)(t_solib *solib, t_sofork_child *));
void			close_pipe(int fd_read, int fd_write);
int				sofork_send_int(int fd, int data);
int				sofork_send_string(int fd, char *data);
int				sofork_send_strings(int fd, char **data);
int				sofork_read_int(int fd);
char			*sofork_read_string(t_solib *solib, int fd);
char			**sofork_read_strings(t_solib *solib, int fd);
char			*sofork_read_file(t_solib *solib, int fd, int size);

#endif
