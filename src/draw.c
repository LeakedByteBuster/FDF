/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:57:09 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/12 20:31:53 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		drawing_unit(int w_w, int w_h, int m_w, int m_h);
void	iso(float *x, float *y, int z, t_data *data);
void	scale_map(t_pt *pt, float *x1, float *y1, t_data *data);

// ** Draws all the tiles of the map

void	draw_tile(t_data *data)
{
	t_pt	pt;

	ft_memset(&pt, 0, sizeof(t_pt));
	while (pt.y < data->height)
	{
		pt.x = 0;
		while (pt.x < data->width)
		{
			if (pt.x < data->width - 1)
				draw_line(pt, pt.x + 1, pt.y, data);
			if (pt.y < data->height - 1)
				draw_line(pt, pt.x, pt.y + 1, data);
			pt.x++;
		}
		pt.y++;
	}
}

// ** Draws a line between point A and B
void	draw_line(t_pt pt, float x1, float y1, t_data *data)
{
	float	x_step;
	float	y_step;
	int		max ;
	int		i;
	int		j;

	i = (int)pt.x;
	j = (int)pt.y;
	iso(&pt.x, &pt.y, data->map_matrix[(int)pt.y][(int)pt.x].z, data);
	iso(&x1, &y1, data->map_matrix[(int)y1][(int)x1].z, data);
	scale_map(&pt, &x1, &y1, data);
	center_map(&pt, &x1, &y1, data);
	x_step = x1 - pt.x;
	y_step = y1 - pt.y;
	max = fmax(fabs(x_step), fabs(y_step));
	x_step /= fmax(fabs(x_step), fabs(y_step));
	y_step /= fmax(fabs(x_step), fabs(y_step));
	while (max-- >= 0)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
			(int)pt.x, (int)pt.y, data->map_matrix[j][i].color);
		pt.x += x_step;
		pt.y += y_step;
	}
}

/*
** Initiates drawing unit (how much distance would be between x and x1)
** drawing unit = (Win_diagonal / 2) / map diagonal
*/
int	drawing_unit(int s_w, int s_h, int m_w, int m_h)
{
	float	screen_diagonal;
	float	map_diagonal;
	float	draw_unit;

	map_diagonal = m_w * m_w + m_h * m_h;
	map_diagonal = sqrt(map_diagonal);
	screen_diagonal = s_w * s_w + s_h * s_h;
	screen_diagonal = sqrt(screen_diagonal);
	draw_unit = (screen_diagonal / 2) / map_diagonal;
	return ((int)draw_unit);
}

void	iso(float *x, float *y, int z, t_data *data)
{
	if (!data->bool)
	{
		if (data->width > 11 && data->width <= 20)
			z /= 6;
		if (data->width < 10)
			z /= 3;
		if (data->width == 21)
			z /= 12;
		if (data->width >= 100 && data->width < 500)
			z /= 3;
		*x = (*x - *y) * cos(1.0890009);
		*y = (*x + *y) * sin(1.5) - z;
	}
	return ;
}

void	scale_map(t_pt *pt, float *x1, float *y1, t_data *data)
{
	int	sc;

	sc = drawing_unit(SCREEN_WIDTH, SCREEN_HEIGHT, data->width, data->height);
	if (sc > 3 && sc <= 6)
		sc *= 1.5;
	if (sc <= 6)
		sc *= 2;
	pt->x *= sc ;
	pt->y *= sc;
	*x1 *= sc;
	*y1 *= sc;
}
