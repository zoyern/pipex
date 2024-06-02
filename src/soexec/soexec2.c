/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soexec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:00:43 by marvin            #+#    #+#             */
/*   Updated: 2024/05/27 22:00:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex/all.h>

void	pipe_swap(int pipefd[2], int filefd[2])
{
	int	tmp;

	tmp = pipefd[0];
	pipefd[0] = filefd[0];
	filefd[0] = tmp;
}

int	exec_fork_child(t_solib *solib, int pipefd[2], char *command)
{
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	return (str_exec(solib, command));
}

int	exec_fork(t_solib *solib, char *command, int pipefd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		solib->close(solib, EXIT_FAILURE);
	if (pid == 0)
		exit(exec_fork_child(solib, pipefd, command));
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int	strs_cmds(t_solib *solib, char **commands, int pipefd[2], int filefd[2])
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (commands[i + 1])
	{
		status = exec_fork(solib, commands[i], pipefd);
		if (pipe(pipefd) == -1)
			solib->close(solib, EXIT_FAILURE);
		pipe_swap(pipefd, filefd);
		i++;
	}
	close(pipefd[1]);
	close(filefd[0]);
	pipefd[1] = filefd[1];
	status = exec_fork(solib, commands[i], pipefd);
	while (wait(&status) != -1)
		continue ;
	close(pipefd[0]);
	close(pipefd[1]);
	return (status);
}

int	strs_exec(t_solib *solib, int fdin, char **commands, int fdout)
{
	int		pipefd[2];
	int		filefd[2];
	int		status;
	int		i;

	if (!commands || !*commands)
		return (0);
	i = 0;
	filefd[1] = fdout;
	filefd[0] = fdin;
	if (pipe(pipefd) == -1)
		solib->close(solib, EXIT_FAILURE);
	pipe_swap(pipefd, filefd);
	status = strs_cmds(solib, commands, pipefd, filefd);
	return (status);
}
