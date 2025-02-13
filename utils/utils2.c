/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:03:20 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/13 18:51:35 by crmunoz-         ###   ########.fr       */
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

char	*fillspace(int len)
{
	int		i;
	char	*dest;

	printf("entro\n");
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	while (i < (len - 1))
	{
		dest[i] = ' ';
		i++;
	}
	dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
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
