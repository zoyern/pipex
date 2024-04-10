/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 01:57:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <pipex.h>

int				solib_memory_init(t_solib *solib);
t_bool			solib_free(t_solib *solib, void *ptr);
void			*solib_malloc(t_solib *solib, unsigned long size);
void			solib_memory_add(t_solib *solib, void *ptr);
void			solib_memory_clear(t_solib *solib);
t_solib_memory	*solib_memory_free(t_solib *solib, void *ptr);
void			solib_memory_show(t_solib *solib);

#endif
