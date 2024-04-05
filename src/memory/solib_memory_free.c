/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_memory_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:17:17 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 08:43:29 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

t_solib_memory	*solib_memory_free(t_solib *solib, void *ptr)
{
	t_solib_memory *current;
	t_solib_memory *tmp;

	if (!solib->memory)
		return (NULL);
	current = solib->memory;
	if ((unsigned long)current->ptr == (unsigned long)ptr)
	{
		solib->memory = current->next;
		return (current);
	}
	while (current->next && current->next->ptr)
	{
		tmp = current->next;
		if ((unsigned long)current->next->ptr == (unsigned long)ptr)
		{
			current->next = current->next->next;
			return (tmp);
		}
		current = tmp;
	}
	return (NULL);
}
