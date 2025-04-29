/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:03:20 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/04/29 15:29:52 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strrchr(char *s, int c)
{
	int				i;
	unsigned char	c2;
	char			*s2;

	s2 = (char *) s;
	c2 = (unsigned char) c;
	i = 0;
	while (s2[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s2[i] == c2)
			return (&s2[i]);
		i--;
	}
	return (NULL);
}

char	*ft_dupspace(char *s1, int len)
{
	int		i;
	char	*dest;
	int		f;

	i = -1;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	while (++i < len && s1[i] != '\0' && s1[i] != '\n')
		dest[i] = s1[i];
	f = i;
	while (i < (len - 1))
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\n';
	dest[++i] = '\0';
	return (dest);
}

long	ft_atol(char *str)
{
	int		i;
	long	sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = ((n * 10) + (str[i] - '0'));
		i++;
	}
	return (n * sign);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	ft_exit(t_map *game)
{
	free_map(game->file);
	free_map(game->map);
	if (game)
	{
		free_struct(game);
		if (game->mlx)
			mlx_close_window(game->mlx);
		free(game);
	}
	exit(1);
}
