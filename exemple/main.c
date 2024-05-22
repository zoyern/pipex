/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:25:55 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exemple.h"

int	main(int argc, char **argv, char **envp)
{
	t_solib		*solib;
	int			*nbrs;
	int			len;

	solib = sonew_libft(sonew_types(argc, argv, envp));
	if (!solib)
		return (1);
	if (!solib->libft)
		return (solib->close(solib, EXIT_FAILURE));
	if (solib->env->argc == 0)
		return (solib->close(solib, EXIT_SUCCESS));
	return (solib->close(solib, EXIT_SUCCESS));
}