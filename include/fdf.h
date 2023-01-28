/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 05:59:28 by mfouadi           #+#    #+#             */
/*   Updated: 2023/01/28 03:33:50 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
// #include "../Libft/get_next_line.h"
#include "../Libft/libft.h"

#define IN 1
#define OUT 0
#define win_width 1980
#define win_height 1080

typedef	struct s_data
{
	int	width;
	int	height;
	int	**z_matrix;
	char	**color;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

typedef	struct s_line
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	
}	t_line;

void	draw_line(void *mlx_ptr, void *win_ptr);
void    get_map(const char *map_name, t_data **data);
void	free_all(int **p, t_data **data);
int	cnt_width(char *s, char c);
int	iscomma(char *line);

#endif // fdf.h
