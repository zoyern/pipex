/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:09 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_strarrfree(t_solib *solib, char **strarr)
{
	int	k;

	k = -1;
	while (strarr[++k])
		solib->free(solib, strarr[k]);
	solib->free(solib, strarr);
	return (1);
}

static char	*strarr_prefixchr(char **strarr, char *target)
{
	while (*strarr && strncmp(target, *strarr, ft_strlen(target)))
		strarr++;
	return (*strarr);
}

static char	*get_cmd(t_solib *solib, char **paths, char *cmd)
{
	char	*temp;
	char	*out;

	while (*paths)
	{
		temp = ft_strjoin(solib, *paths, "/");
		out = ft_strjoin(solib, temp, cmd);
		solib->free(solib, temp);
		if (access(out, 0) == 0)
			return (out);
		solib->free(solib, out);
		paths++;
	}
	temp = ft_strjoin(solib, "pipex: ", cmd);
	out = ft_strjoin(solib, temp, ": command not found\n");
	write(2, out, ft_strlen(out));
	solib->free(solib, out);
	solib->free(solib, temp);
	return (0);
}

int	str_exec(t_solib *solib, char *str)
{
	static char	**paths = 0;
	char		*path;
	char		**argv;
	char		*cmd;
	int			ret;

	path = strarr_prefixchr(solib->cmd->envp, "PATH");
	if (!path)
		return (1);
	paths = ft_split(solib, path + 5, ':');
	if (!paths)
		return (1);
	argv = ft_split(solib, str, ' ');
	if (!argv && ft_strarrfree(solib, paths))
		return (1);
	cmd = get_cmd(solib, paths, argv[0]);
	ft_strarrfree(solib, paths);
	if (!cmd && ft_strarrfree(solib, argv))
		return (1);
	ret = execve(cmd, argv, solib->cmd->envp);
	solib->free(solib, cmd);
	ft_strarrfree(solib, argv);
	return (ret);
}


int	myexecchild(t_solib *solib, t_sofork_child *child)
{
	int	read;
	int	write;
	read = child->get->integer(child->this->read);
	write = child->get->integer(child->this->read);
	dup2(read, 0);
	dup2(write, 1);
	return (str_exec(solib, child->get->string(solib, child->this->read)));
}

int	solib_exec_fd(t_solib *solib, char *command, int read, int write)
{
	t_sofork_parent *parent;

	parent = solib->new->fork(solib, myexecchild);
	parent->send->integer(parent->this->write, read);
	parent->send->integer(parent->this->write, write);
	parent->send->string(parent->this->write, command);
	return (read);
}

char	*solib_shell(t_solib *solib, char *command)
{
	t_sofork_parent *parent;

	parent = solib->new->fork(solib, myexecchild);
	parent->send->integer(parent->this->write, parent->pipes->child->read);
	parent->send->integer(parent->this->write, parent->pipes->child->write);
	parent->send->string(parent->this->write, command);
	return (parent->get->file(solib, parent->this->read, 1024));
}