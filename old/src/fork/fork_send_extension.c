/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_extension2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:26:11 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:26:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int sofork_send_int(int fd, int data)
{
	int integer = data;
	if (write_data_to_pipe(fd, &integer, sizeof(int)))
		return (1);
	return (0);
}

int sofork_send_string(int fd, char *data)
{
	int	lenght;

	lenght = ft_strlen(data);
	if (sofork_send_int(fd, lenght))
		return (1);
	if (write_data_to_pipe(fd, data, lenght))
		return (1);
	return (0);
}

int sofork_send_strings(int fd, char **data)
{
	int lenght;

	lenght = 0;
	if (data)
		while (data[lenght])
			lenght++;
	if (sofork_send_int(fd, lenght))
		return (1);
	lenght = 0;
	while (data[lenght])
	{
		if (sofork_send_string(fd, data[lenght++]))
			return (1);
	}
	return (0);
}