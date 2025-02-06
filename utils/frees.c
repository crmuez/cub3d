/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:11:35 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/06 17:20:17 by crmunoz-         ###   ########.fr       */
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
	{
		printf("Invalid arguments\n");
		return (1);
	}
	else if (err == '1')
	{
		printf("Malloc error\n");
		return (1);
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
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

int	ft_isvalid(unsigned char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_' || c == '-'
		|| c == '.' || c == '/')
		return (1);
	else
		return (0);
}

char	*ft_strncpy(char *src)
{
	int		j;
	int		i;
	char	*dst;
	int		len;

	j = 0;
	i = 0;
	len = ft_strlen(src);
	if (!src)
		return (NULL);
	write (1, "no peto aqui 4.0\n", 17);
	while (src[i] != '.' && src[i + 1] != '/')
		i++;
	write (1, "no peto aqui 4.1\n", 17);
	len = len - i;
	dst = malloc(sizeof(char) * len + 1);
	write (1, "no peto aqui 4.2\n", 17);
	while (src[i] && (ft_isvalid(src[i])))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	write (1, "no peto aqui 4.3\n", 17);
	return (dst);
}
