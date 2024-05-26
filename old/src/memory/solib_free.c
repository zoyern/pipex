/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:20:45 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 08:37:22 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

t_bool	solib_free(t_solib *solib, void *ptr)
{
	t_solib_memory	*memory;

	if (ptr)
	{
		memory = solib_memory_free(solib, ptr);
		if (memory)
		{
			free(memory->ptr);
			memory->ptr = NULL;
			free(memory);
			memory = NULL;
			return (FALSE);
		}
	}
	return (TRUE);
}
