/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:16:39 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 08:33:40 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

int	solib_memory_init(t_solib *solib)
{
	solib->memory = (t_solib_memory *)malloc(sizeof(t_solib_memory));
	if (!solib->memory)
		return (1);
	solib->memory->ptr = NULL;
	solib->memory->next = NULL;
	return (0);
}
