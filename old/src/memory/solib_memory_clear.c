/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_memory_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:17:31 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 08:43:10 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

void	solib_memory_clear(t_solib *solib)
{
	t_solib_memory	*current;
	t_solib_memory	*tmp;

	current = solib->memory;
	while (current->ptr)
	{
		tmp = current->next;
		solib->free(solib, current->ptr);
		current = tmp;
	}
	free(current);
	solib->memory = NULL;
}
