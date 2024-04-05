/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:31:31 by marvin            #+#    #+#             */
/*   Updated: 2024/04/01 21:31:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pipex.h>

unsigned long ft_strlen(const char *s)
{
	unsigned long i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	unsigned long len;
	char *t;

	len = ft_strlen(s);
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	while (*s)
		*t++ = *s++;
	*t = '\0';
	return (t -= len);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	unsigned long len;
	char *t;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	while (*s1)
		*t++ = *s1++;
	while (*s2)
		*t++ = *s2++;
	*t = '\0';
	return (t -= len);
}

void *ft_memalloc(size_t size)
{
	char *i;
	size_t x;

	x = 0;
	if ((i = malloc(size)) == NULL)
		return (NULL);
	while (x < size)
	{
		i[x] = 0;
		x++;
	}
	return (i);
}

char *get_input()
{
	char *buf;
	char *temp;
	char *leak;
	int count;
	int result;

	count = 0;
	buf = ft_memalloc(2);
	temp = ft_memalloc(2);
	buf[0] = 0;
	temp[0] = 0;
	while ((result = read(0, buf, 1)) && (buf[0] != '\n'))
	{
		leak = temp;
		temp = ft_strjoin(temp, buf);
		free(leak);
		count = 1;
	}
	if (buf[0] == '\n' && count != 1)
		return (free(temp), buf);
	else
		return (free(buf), temp);
}