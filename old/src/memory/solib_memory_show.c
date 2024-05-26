/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib_memory_show.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:17:04 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 08:44:42 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

void	solib_memory_show(t_solib *solib)
{
	t_solib_memory	*current;

	current = solib->memory;
	while (current)
	{
		printf("%p -> %p\t\tnext : %p\n", current, current->ptr, current->next);
		current = current->next;
	}
}
