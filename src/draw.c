/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:57:09 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/08 00:09:56 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
int drawing_unit(int w_w, int w_h, int m_w, int m_h);
void iso(float *x, float *y, float z);

// ** Draws all the tiles of the map
void draw_tile(t_data *data)
{
	int	x;
	int	y;
	
	y = 0; // Later, can give x,y st.point to start draw the map centered
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				draw_line(x, y, x+1, y, data);
			if (y < data->height - 1)
				draw_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}

// ** Draws a line between point A and B
void draw_line(float x, float y, float x1, float y1, t_data *data)
{
	float	x_step;
	float	y_step;
	int	scale;
	int i = (int)x;
	int j = (int)y;
	// float z = data->map_matrix[(int)y][(int)x].z;
	// float z1 = data->map_matrix[(int)y1][(int)x1].z;
	// tile = malloc (sizeof(t_tile));
	// if (!tile)
	// return NULL;
scale = drawing_unit(SCREEN_WIDTH, SCREEN_HEIGHT, data->width, data->height);
// printf("%d", scale);


/***** Elarging distance between points ******/
	x *= scale;
	y *= scale;
	x1 *= scale;
	y1 *= scale;

/*** Isometric view ****/
	// iso(&x, &y, z);
	// iso(&x, &y, z1);
	// printf("\n%f\n", z1);

	x_step = x1 - x;
	y_step = y1 - y;
	x_step /= fmax(fabs(x_step), fabs(y_step));
	y_step /= fmax(fabs(x_step), fabs(y_step));

	/***** translates x and y *****/
	x += SCREEN_WIDTH / 4;
	y += SCREEN_HEIGHT / 5;
	x1 += SCREEN_WIDTH / 4;
	y1 += SCREEN_HEIGHT / 5;

	// printf("color=%d | i=%d | j=%d | z=%d\n", data->map_matrix[j][i].color, j, i, data->map_matrix[i][j].z);

	while ((int)x != (int)x1 || (int)y != (int)y1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)x, (int)y, data->map_matrix[j][i].color);
		x += x_step;
		y += y_step;
	}
	return ;
}

/*
** Initiates drawing unit (how much distance would be between x and x1)
** drawing unit = (Win_diagonal / 2) / map diagonal
*/
int drawing_unit(int s_w, int s_h, int m_w, int m_h)
{
	float screen_diagonal;
	float map_diagonal;
	float draw_unit;

	map_diagonal = m_w * m_w + m_h * m_h;
	map_diagonal = sqrt(map_diagonal);
	screen_diagonal = s_w * s_w + s_h * s_h;
	screen_diagonal = sqrt(screen_diagonal);
	draw_unit = (screen_diagonal / 2) / map_diagonal;
	return ((int)draw_unit);
}

void	iso(float *x, float *y, float z)
{
	// This equation maps the x and y values to a new x value
	/*  
	**	The cos(0.8) term is the cosine of the angle of the isometric projection
	**	isometric projections are typically done with an angle around 30 degrees
	*/
	//  (*x - *y) horizontal difference between x and y,
	*x = (*x - *y) * cos(0.8);

	// This equation maps the x, y, and z values to a new y value.
	// The sin(0.8) term is the sine of the angle of the isometric projection
	// The *x + *y term calculates the horizontal sum of x and y, then scaled by the sine of the angle
	/*
	** The '- *z' term maps the z height to the y axis, giving the illusion of a 3D view
	** The '-' sign is used to invert the height, so that positive z values are mapped to lower y values and negative z values are mapped to higher y values.
	*/
	*y = (*x + *y) * sin(0.8) - z;
}
