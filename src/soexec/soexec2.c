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

# include <pipex/all.h>

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

int	exec_fork(t_solib *solib, int *pid, char *command, int pipefd[2])
{
	int	status;

	*pid = fork();
	if (*pid == -1)
		solib->close(solib, EXIT_FAILURE);
	if (*pid == 0)
		exit(exec_fork_child(solib, pipefd, command));
	waitpid(*pid, &status, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (status);
}

int	strs_exec(t_solib *solib, int fdin, char **commands, int fdout)
{
	int		pipefd[2];
	int		filefd[2];
	int		pid;
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
	while (commands[i + 1])
	{
		status = exec_fork(solib, &pid, commands[i], pipefd);
		if (status)
			break;
		if (pipe(pipefd) == -1)
       		solib->close(solib, EXIT_FAILURE);
		pipe_swap(pipefd, filefd);
		i++;
	}
	if (status)
		return (status);
	close(pipefd[1]);
	close(filefd[0]);
	pipefd[1] = filefd[1];
	status = exec_fork(solib, &pid, commands[i], pipefd);
	if (status)
		return (status);
	return (0);
}
