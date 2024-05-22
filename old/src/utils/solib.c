/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:41:10 by marvin            #+#    #+#             */
/*   Updated: 2024/04/18 11:07:35 by almounib         ###   ########.fr       */
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
	int			i;

	cmd = (t_solib_cmd *)solib->malloc(solib, sizeof(t_solib_cmd));
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->name = NULL;
	if (argv)
	{
		cmd->name = ft_strdup(solib, argv[0]);
		if (argc > 0)
		{
			argv++;
			i = 0;
			while (i < argc && argv[i])
				i++;
			cmd->argv = (char **)solib->malloc(solib, sizeof(char *) * (i + 1));
			cmd->argc = i;
			i = -1;
			while (++i < cmd->argc && argv[i])
				cmd->argv[i] = ft_strdup(solib, argv[i]);
			cmd->argv[i] = 0;
		}
	}
	cmd->envp = envp;
	solib->cmd = cmd;

	/*printf("SOLIB CMD --- \n");
	printf("-name %s\n", cmd->name);
	printf("-argc %d\n", cmd->argc);
	printf("-envp %p\n", cmd->envp);
	ft_putstrs(1, cmd->argv);
	printf("---- SOLIB CMD ---- \n");*/
	return (0);
}

int solib_openfd(char *path, int flags)
{
	int fd;

	if (!path)
		return (1);
	fd = open(path, flags , 0644);
	if (fd < 0)
		return (1);
	return (fd);
}

char *solib_read_file(t_solib *solib, int fd, int size)
{
	char	*buf;
	char	*data;

	data = NULL;
	buf = ft_memalloc(solib, sizeof(char) * size);
	while (read(fd, buf, size) > 0)
		ft_strmcat(solib, &data, buf);
	solib->free(solib, buf);
	return (data);
}


int	solib_validfd(int fd)
{
	if (fd < 0 || fd > 1024 || read(fd, 0, 0) < 0)
		return (FALSE);
	return (TRUE);
}


int	pipexchild(t_solib *solib, t_sofork_child *child)
{
	t_sofork_parent	*parent;
	char **commands;
	int	index;
	int in;
	int out;

	commands = child->get->strings(solib, child->this->read);
	index = child->get->integer(child->this->read);
	in = child->get->integer(child->this->read);
	out = child->get->integer(child->this->read);
	if (index < 0)
		return (child->send->integer(child->this->write, in), 0);
	parent = solib->new->fork(solib, pipexchild);
	parent->send->strings(parent->this->write, commands);
	parent->send->integer(parent->this->write, index - 1);
	parent->send->integer(parent->this->write,in);
	parent->send->integer(parent->this->write, out);
	parent->wait(parent, 0, 0);
	in = parent->get->integer(parent->this->read);
	child->send->integer(child->this->write, child->pipes->child->read);
	if (commands[index + 1])
		out = child->pipes->child->write;
	return (solib->exec(solib, commands[index], in,	out));
}

void	solib_pipex(t_solib *solib, int in, int out, char **commands)
{
	ft_putstrs(1, commands);
	t_sofork_parent	*parent;
	int	lenght;

	lenght = 0;
	if (!solib || !commands || !solib->cmd->envp)
		return ;
	while (commands[lenght])
		lenght++;
	if (in < 0 || out < 0 || lenght <= 0)
		return ;
	parent = solib->new->fork(solib, pipexchild);
	parent->send->strings(parent->this->write, commands);
	parent->send->integer(parent->this->write, lenght - 1);
	parent->send->integer(parent->this->write, in);
	parent->send->integer(parent->this->write, out);
	parent->wait(parent, 0, 0);
	in = parent->get->integer(parent->this->read);

	parent->close(parent);
}


t_solib *sonew(int argc, char **argv, char **envp)
{
	t_solib *solib;

	solib = (t_solib *)malloc(sizeof(t_solib));
	if (!solib)
		return (NULL);
	if (solib_memory_init(solib))
		return (free(solib), NULL);
	solib->malloc = solib_malloc;
	solib->free = solib_free;
	solib->close = solib_close;
	if (solib_cmd_init(solib, argc, argv, envp))
		return (solib->close(solib, EXIT_SUCCESS), NULL);
	solib->shell = solib_shell;
	solib->exec = solib_exec_fd;
	solib->open = solib_openfd;
	solib->read_file = solib_read_file;
	solib->pipex = solib_pipex;
	solib_new_init(solib);
	return (solib);
}