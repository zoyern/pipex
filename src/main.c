/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/04/10 20:48:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char **get_commands_for_pipex(t_solib *solib)
{
	char	**commands;
	int		i;

	if (!solib || solib->cmd->argc < 3 || !solib->cmd->argv)
		return (NULL);
	commands = solib->malloc(solib, sizeof(char *) * (solib->cmd->argc - 1));
	i = 0;
	while (solib->cmd->argv[i + 1] && solib->cmd->argv[i + 2])
	{
		commands[i] = ft_strdup(solib,solib->cmd->argv[i + 1]);
		i++;
	}
	commands[i] = 0;
	return (commands);
}
/*int solib_pipex_openfd(char *path_in, char *path_out, int *in, int *out)
{
	*in = open(path_in, O_RDWR , 0644);
	if (*in < 0)
		return (1);
	*out = open(path_out, O_RDWR , 0644);
	if (*out < 0)
		return (close(*in), 1);
	printf("fd in : %d -- fd out : %d\n", *in, *out);
	return (0);
}*/

int main(int argc, char **argv, char **envp) {
	t_solib	*solib;
	char	**commands;
	int fdin;
	int fdout;

	fdin = 0;
	fdout = 1;
	solib = sonew(argc, argv, envp);
	if (!solib)
		return (1);
	commands = get_commands_for_pipex(solib);
	if (solib->cmd->argc >= 3)
	{
		fdin = solib->open(solib->cmd->argv[0], O_RDWR);
		fdout = solib->open(solib->cmd->argv[solib->cmd->argc - 1], O_RDWR);
	}
	printf("fd in : %d -- fd out : %d\n", fdin , fdout);
	solib->pipex( solib, fdin, fdout, commands);
	solib->close(solib, EXIT_SUCCESS);
    return (0);
}


