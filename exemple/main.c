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

char	**get_commands(t_solib *solib)
{
	char	**commands;

	commands = solib->env->argv;
	commands++;
	commands[solib->env->argc - 2] = 0;
	return (commands);
}

int	main(int argc, char **argv, char **envp)
{
	t_solib		*solib;

	solib = sonew_types(argc, argv, envp);
	if (!solib)
		return (1);
	solib = sonew_libft(solib);
	if (solib->env->argc > 3)
		pipex(solib, solib->env->argv[0], get_commands(solib), solib->env->argv[solib->env->argc - 1]);
	else
		solib->print("%Ccf2a84(Wrong number of argument (%C2ab3cf(%d)) needed (%C2ab3cf(%d+)))\n", solib->env->argc, 4);
	return (solib->close(solib, EXIT_SUCCESS));
}
