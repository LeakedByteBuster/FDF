/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:38:24 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/12 20:20:56 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ** Hex digits in lowercase and uppercase
#define LOW_HEX "0123456789abcdef"
#define UPP_HEX "0123456789ABCDEF"

// Frees the char **
void	free_split(char **s)
{
	int	i;

	if (!s && !(*s))
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

// Frees the t_tile **
void	free_matrix(t_tile **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

// ** Checks whether the map is empty or not
int	map_is_empty(char *s)
{
	char	**line;

	line = ft_split(s, ' ');
	if (!line)
		return (perror("Given map is empty"), 1);
	return (free_split(line), 0);
}

//** Returns the corresponding decimal value of the given hexa character
int	is_hexa(char c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (-1);
	while (i < 16)
	{
		if ((LOW_HEX[i] == c) || (UPP_HEX[i] == c))
			return (i);
		i++;
	}
	return (-1);
}

/* 
** Converts hexadecimal number to decimal number
** Creating a place for the next digit by mulptiplying by 16, then adding
** the index that corresponds to the correct decimal value digit
*/
int	ft_strtol(char *str)
{
	int	res;
	int	index;

	res = 0;
	if (!str)
		return (0x00FFFFFF);
	while (*str)
	{
		index = is_hexa(*str);
		if (index == -1)
			return (res);
		res = (res * 16) + index;
		str++;
	}
	return (res);
}
