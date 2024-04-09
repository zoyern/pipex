/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:41:10 by marvin            #+#    #+#             */
/*   Updated: 2024/04/05 02:41:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

int solib_close(t_solib *solib, int state)
{
	if (solib)
	{
		if (solib->memory)
			solib_memory_clear(solib);
		free(solib);
		solib = NULL;
	}
	if (state)
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	solib_new_init(t_solib *solib)
{
	t_solib_new	*event_new;

	event_new = (t_solib_new *)solib->malloc(solib, sizeof(t_solib_new));
	event_new->fork = new_fork;
	event_new->pipe = new_pipe;
	event_new->pipe_data = new_pipe_data;
	solib->new = event_new;
}

int	solib_cmd_init(t_solib *solib, int argc, char **argv, char **envp)
{
	t_solib_cmd *cmd;

	cmd = (t_solib_cmd *)solib->malloc(solib, sizeof(t_solib_cmd));
	cmd->name = argv[0];
	cmd->argc = argc - 1;
	cmd->argv = argv + 1;
	cmd->envp = envp;
	solib->cmd = cmd;
	return (0);
}

t_solib *sonew(int argc, char **argv, char **envp)
{
	t_solib *solib;

	if (!envp)
		return (NULL);
	solib = (t_solib *)malloc(sizeof(t_solib));
	if (!solib)
		return (NULL);
	solib_memory_init(solib);
	solib->close = solib_close;
	solib->malloc = solib_malloc;
	solib->free = solib_free;
	solib->shell = solib_shell;
	solib->exec = solib_exec_fd;
	solib_cmd_init(solib, argc, argv, envp);
	solib_new_init(solib);
	return (solib);
}