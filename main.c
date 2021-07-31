/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:59:56 by mtournay          #+#    #+#             */
/*   Updated: 2021/07/30 18:27:51 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct s_set
{
	double	height;
	double	width;
	int		x;
	int		y;
	int		iteration;
	double	zR;
	double	zI;
	double	cR;
	double	cI;
	double 	Rsquared;
	double	Isquared;
	int 	color;
	int 	red;
	int		blue;
	int		green;
	int 	transparency;
}				t_set;

typedef struct	s_data 
{
	void	    *img;
	char	    *addr;
	int		    bits_per_pixel;
	int		    line_length;
	int		    endian;
	void    	*mlx;
    void    	*mlx_win;
	void		*img2;
	void		*addr2;
	int			bol_img1;
	int 		color_shift;
	int			color_max;
	int			color_min;
	char		matrix[720][1280];
	t_set		*mndl;
}				t_data;

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put1(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr2 + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_data *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vars->mlx, vars->mlx_win);
		exit(1);
	}
	return(0);
}

int close2(t_data *vars)
{
	mlx_destroy_image(vars->mlx, vars->mlx_win);
	exit(1);
	return(0);
}

int 	mandelbrot_set_matrix(t_data *vars)
{
	vars->mndl->y = 0;
	while (vars->mndl->y < vars->mndl->height)
	{
		vars->mndl->x = 0;
		while (vars->mndl->x < vars->mndl->width)
		{
			vars->mndl->zR = 0.0;
			vars->mndl->zI = 0.0;
			vars->mndl->cR = (vars->mndl->x - vars->mndl->width/2.0) * 4.0/vars->mndl->width;
			vars->mndl->cI = (vars->mndl->y - vars->mndl->height/2.0) * 4.0/vars->mndl->width;
			vars->mndl->Rsquared = pow(vars->mndl->zR, 2);
			vars->mndl->Isquared = pow(vars->mndl->zI, 2);
			vars->mndl->iteration = 0;
			while (vars->mndl->Rsquared + vars->mndl->Isquared <= 4.0 && vars->mndl->iteration < 255)
			{
				vars->mndl->zI = vars->mndl->zR * vars->mndl->zI * 2;
				vars->mndl->zI += vars->mndl->cI;
				vars->mndl->zR = vars->mndl->Rsquared - vars->mndl->Isquared;
				vars->mndl->zR += vars->mndl->cR;
				vars->mndl->Rsquared = vars->mndl->zR * vars->mndl->zR;
				vars->mndl->Isquared = vars->mndl->zI * vars->mndl->zI;
				vars->mndl->iteration++;
			}
			if (vars->mndl->Rsquared + vars->mndl->Isquared <= 4.0)
				vars->matrix[vars->mndl->y][vars->mndl->x] = 0;
			else
				vars->matrix[vars->mndl->y][vars->mndl->x] = 1;
			vars->mndl->x++;
		}
		vars->mndl->y++;
	}
	return(1);
}

int		mandelbrot_set(t_data *vars, int bol_img, int color_shift)
{
	vars->mndl->y = 0;
	while (vars->mndl->y < vars->mndl->height)
	{
		vars->mndl->x = 0;
		while (vars->mndl->x < vars->mndl->width && vars->mndl->x < 900)
		{
			vars->mndl->color = 0;
			vars->mndl->red = 0;
			vars->mndl->blue = 0;
			vars->mndl->green = 0;
			vars->mndl->zR = 0.0;
			vars->mndl->zI = 0.0;
			vars->mndl->cR = (vars->mndl->x - vars->mndl->width/2.0) * 4.0/vars->mndl->width;
			vars->mndl->cI = (vars->mndl->y - vars->mndl->height/2.0) * 4.0/vars->mndl->width;
			vars->mndl->Rsquared = pow(vars->mndl->zR, 2);
			vars->mndl->Isquared = pow(vars->mndl->zI, 2);
			vars->mndl->iteration = 0;
			while (vars->mndl->Rsquared + vars->mndl->Isquared <= 4.0 && vars->mndl->iteration < 1020 && vars->matrix[vars->mndl->y][vars->mndl->x])
			{
				vars->mndl->zI = vars->mndl->zR * vars->mndl->zI * 2;
				vars->mndl->zI += vars->mndl->cI;
				vars->mndl->zR = vars->mndl->Rsquared - vars->mndl->Isquared;
				vars->mndl->zR += vars->mndl->cR;
				vars->mndl->Rsquared = vars->mndl->zR * vars->mndl->zR;
				vars->mndl->Isquared = vars->mndl->zI * vars->mndl->zI;
				vars->mndl->iteration++;
				if (vars->mndl->iteration <= 10*4)
					vars->mndl->red+= color_shift;
				// if (vars->mndl->iteration <= 5)
				// 	vars->mndl->green+= 5 + color_shift;
				// if (vars->mndl->iteration <= 2)
				// 	vars->mndl->blue+= 2 + color_shift;
			}
			if (vars->mndl->iteration <= 255*4 && vars->mndl->iteration)
				vars->mndl->red+= vars->mndl->iteration/4;
			if (vars->mndl->iteration <= 150*4 && vars->mndl->iteration)
				vars->mndl->green+= vars->mndl->iteration/4;
			if (vars->mndl->iteration <= 255*4 && vars->mndl->iteration)
				vars->mndl->blue+= vars->mndl->iteration/2 -8;
			vars->mndl->color = create_trgb(vars->mndl->transparency, vars->mndl->red, vars->mndl->green, vars->mndl->blue);
			if (vars->mndl->Rsquared + vars->mndl->Isquared <= 4.0)
			{
				if (bol_img)
					my_mlx_pixel_put1(vars, vars->mndl->x, vars->mndl->y, 0x000000);
				else
					my_mlx_pixel_put2(vars, vars->mndl->x, vars->mndl->y, 0x000000);
			}
			else
			{
				if (bol_img)
					my_mlx_pixel_put1(vars, vars->mndl->x, vars->mndl->y, vars->mndl->color);
				else
					my_mlx_pixel_put2(vars, vars->mndl->x, vars->mndl->y, vars->mndl->color);
			}
				
			vars->mndl->x++;
		}
		vars->mndl->y++;
	}
	return(1);
}

int instance(t_data *vars)
{
	mandelbrot_set(vars, 1, vars->color_shift);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
	if (vars->color_shift < 100 && vars->color_min == 1)
	{
		vars->color_shift++;
		vars->color_min = 1;
		vars->color_max = 0;
	}
	if (vars->color_shift > 0 && vars->color_max == 1)
	{
		vars->color_shift--;
		vars->color_min = 0;
		vars->color_max = 1;
	}
	if (vars->color_shift == 100)
		vars->color_max = 1;
	if (vars->color_shift == 0)
		vars->color_min = 1;
	return(0);
}

int main()
{
    t_data	*vars;
	vars = malloc(sizeof(t_data));
	vars->mndl = malloc(sizeof(t_set));
	vars->mndl->x = 0;
	vars->mndl->y = 0;
	vars->color_shift = 1;
	vars->color_max = 0;
	vars->color_min = 1;
	vars->bol_img1 = 0;
	vars->mndl->transparency = 0;
	vars->mndl->height = 720.0;
	vars->mndl->width = 1280.0;
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, 900, 720, "Hello world!");
	vars->img = mlx_new_image(vars->mlx, vars->mndl->width, vars->mndl->height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
								&vars->endian);
	vars->img2 = mlx_new_image(vars->mlx, vars->mndl->width, vars->mndl->height);
	vars->addr2 = mlx_get_data_addr(vars->img2, &vars->bits_per_pixel, &vars->line_length,
								&vars->endian);


	
	// while (vars->mndl->y < vars->mndl->height)
	// {
	// 	vars->mndl->x = 0;
	// 	while (vars->mndl->x < vars->mndl->width)
	// 	{
	// 		vars->mndl->color = 0;
	// 		vars->mndl->red = 0;
	// 		vars->mndl->blue = 0;
	// 		vars->mndl->green = 0;
	// 		vars->mndl->zR = 0.0;
	// 		vars->mndl->zI = 0.0;
	// 		vars->mndl->cR = (vars->mndl->x - vars->mndl->width/2.0) * 4.0/vars->mndl->width;
	// 		vars->mndl->cI = (vars->mndl->y - vars->mndl->height/2.0) * 4.0/vars->mndl->width;
	// 		vars->mndl->Rsquared = vars->mndl->zR * vars->mndl->zR;
	// 		vars->mndl->Isquared = vars->mndl->zI * vars->mndl->zI;
	// 		vars->mndl->iteration = 0;
	// 		while (vars->mndl->Rsquared + vars->mndl->Isquared <= 4.0 && vars->mndl->iteration < 255)
	// 		{
	// 			vars->mndl->zI = vars->mndl->zR * vars->mndl->zI * 2;
	// 			vars->mndl->zI += vars->mndl->cI;
	// 			vars->mndl->zR = vars->mndl->Rsquared - vars->mndl->Isquared;
	// 			vars->mndl->zR += vars->mndl->cR;
	// 			vars->mndl->Rsquared = vars->mndl->zR * vars->mndl->zR;
	// 			vars->mndl->Isquared = vars->mndl->zI * vars->mndl->zI;
	// 			vars->mndl->iteration++;
	// 			if (vars->mndl->iteration <= 100)
	// 				vars->mndl->red+=5;
	// 			if (vars->mndl->iteration <= 150)
	// 				vars->mndl->green+=3;
	// 			if (vars->mndl->iteration <= 255)
	// 				vars->mndl->blue+=2;
	// 		}
	// 		vars->mndl->color = create_trgb(vars->mndl->transparency, vars->mndl->red, vars->mndl->green, vars->mndl->blue);
	// 		if (vars->mndl->Rsquared + vars->mndl->Isquared <= 4.0)
	// 			my_mlx_pixel_put2(vars, vars->mndl->x, vars->mndl->y, 0x000000);
	// 		else
	// 			my_mlx_pixel_put2(vars, vars->mndl->x, vars->mndl->y, vars->mndl->color);
	// 		vars->mndl->x++;
	// 	}
	// 	vars->mndl->y++;
	// }
	// mandelbrot_set(vars, 1, 1);
	// mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
	mandelbrot_set_matrix(vars);
	mlx_loop_hook(vars->mlx, instance, vars);
	mlx_hook(vars->mlx_win, 2, 1L<<0, close, vars);
	// mlx_hook(vars->mlx_win, 6, 0, )
	mlx_hook(vars->mlx_win, 17, 1L<<5, close2, vars);
	mlx_loop(vars->mlx);
}


