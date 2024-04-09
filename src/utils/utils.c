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

char *ft_strdup(t_solib *solib, const char *s)
{
	unsigned long len;
	char *t;

	len = ft_strlen(s);
	t = (char *)solib->malloc(solib, sizeof(char) * (len + 1));
	while (*s)
		*t++ = *s++;
	*t = '\0';
	return (t -= len);
}

char *ft_strjoin(t_solib *solib, char const *s1, char const *s2)
{
	unsigned long len;
	char *t;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	t = (char *)solib->malloc(solib, sizeof(char) * (len + 1));
	while (*s1)
		*t++ = *s1++;
	while (*s2)
		*t++ = *s2++;
	*t = '\0';
	return (t -= len);
}

void *ft_memalloc(t_solib *solib, size_t size)
{
	char *i;
	size_t x;

	x = 0;
	i = solib->malloc(solib, size);
	while (x < size)
	{
		i[x] = 0;
		x++;
	}
	return (i);
}

char *get_input(t_solib *solib)
{
	char *buf;
	char *temp;
	char *leak;
	int count;
	int result;

	count = 0;
	buf = ft_memalloc(solib, 2);
	temp = ft_memalloc(solib, 2);
	buf[0] = 0;
	temp[0] = 0;
	while ((result = read(0, buf, 1)) && (buf[0] != '\n'))
	{
		leak = temp;
		temp = ft_strjoin(solib, temp, buf);
		solib->free(solib, leak);
		count = 1;
	}
	if (buf[0] == '\n' && count != 1)
		return (solib->free(solib, temp), buf);
	else
		return (solib->free(solib, buf), temp);
}

void	ft_putstrs(int fd, char **strs)
{
	dprintf(fd, "-----------------\n");
	while (*strs)
	{
		dprintf(fd, "%s\n", *strs++);
	}
	dprintf(fd, "-----------------\n");
}

static int	ft_len(int nbr)
{
	int len;

	len = 0;
	len = (nbr <= 0 ? 1 : 0);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(t_solib *solib, int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*alpha;

	sign = (n < 0 ? 1 : 0);
	alpha = NULL;
	len = ft_len(n);
	nbr = (n < 0 ? -n : n);
	alpha = solib->malloc(solib, sizeof(char) * len + 1);
	alpha[len--] = '\0';
	while (len >= 0)
	{
		alpha[len] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	if (sign == 1)
		alpha[0] = '-';
	return (alpha);
}