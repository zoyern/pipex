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

#endif
