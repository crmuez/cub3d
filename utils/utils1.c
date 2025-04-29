/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:11:35 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/04/29 20:40:52 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i] != NULL)
		{
			free (map[i]);
			i++;
		}
		free (map);
	}
}

int	ft_error(int err)
{
	if (err == '0')
		write(2, "Error\nInvalid arguments\n", 24);
	else if (err == '1')
		write(2, "Error\nMalloc error\n", 19);
	else if (err == '2')
		write(2, "Error\nInvalid map\n", 18);
	else if (err == '3')
		write(2, "Error\nInvalid map extension\n", 28);
	else if (err == '4')
		write(2, "Error\nInvalid rgb\n", 18);
	else if (err == '5')
	{
		write(2, "Error\nInvalid file\n", 19);
		exit ;
	}
	return (-1);
}

int	ft_isspace(int c)
{
	if (!c)
		return (2);
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	count_lines(char *argv)
{
	int		i;
	int		fd;
	char	*map;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	map = get_next_line(fd);
	i = 0;
	while (map)
	{
		free(map);
		i++;
		map = get_next_line(fd);
	}
	close(fd);
	if (i < 9)
		return (ft_error('2'));
	return (i);
}
