/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_read_extension.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:29:48 by marvin            #+#    #+#             */
/*   Updated: 2024/04/08 15:29:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int sofork_read_int(int fd)
{
	int	data;

	data = 0;
	if (read(fd, &data, sizeof(int)) == -1)
        perror("pipex: read int");
	return (data);
}

char *sofork_read_string(t_solib *solib, int fd)
{
	int 	lenght;
	char	*data;
	int		watch;

	lenght = sofork_read_int(fd);
	//printf("---- READ string FD : %d | lenght : %d\n",fd, lenght);
	data = (char *)solib->malloc(solib,sizeof(char) * (lenght + 1));
	watch = read(fd, data, lenght);
	if (watch == -1)
        return (perror("pipex: read string"), NULL);
	else if (watch != lenght)
		return (perror("pipex: read string size error"), NULL);
	data[lenght] = 0;
	//printf("---- je lis : %d > %d -- %s\n", fd, lenght, data);
	return (data);
}

char **sofork_read_strings(t_solib *solib, int fd)
{
	int 	lenght;
	int 	i;
	char	**data;

	lenght = sofork_read_int(fd);
	//printf("-- READ STRS FD : %d | lenght : %d\n",fd, lenght);
	if (lenght < 1)
		return (NULL);
	data = (char **)solib->malloc(solib,sizeof(char *) * (lenght + 1));
	i = 0;
	while (i < lenght)
		data[i++] = sofork_read_string(solib, fd);
	data[i] = 0;
	return (data);
}

char *sofork_read_file(t_solib *solib, int fd, int size)
{
	char	*buf;
	char	*data;

	data = ft_strdup(solib, "");
	buf = ft_memalloc(solib, sizeof(char) * size + 1);
	while (read(fd, buf, size) > 0)
		ft_strmcat(solib, &data, buf);
	solib->free(solib, buf);
	return (data);
}

