/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_memory_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:15:43 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 08:38:42 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

void	solib_memory_add(t_solib *solib, void *ptr)
{
	t_solib_memory	*memory;

	memory = (t_solib_memory *)malloc(sizeof(t_solib_memory));
	if (!memory)
		solib->close(solib, EXIT_FAILURE);
	memory->ptr = ptr;
	memory->next = solib->memory;
	solib->memory = memory;
}
