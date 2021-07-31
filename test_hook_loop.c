/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hook_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:19:57 by mtournay          #+#    #+#             */
/*   Updated: 2021/06/19 16:55:30 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <math.h>



typedef struct	s_vars {
	void	    *mlx;
	void	    *win;
    void	    *img;
	char	    *addr;
	int		    bits_per_pixel;
	int		    line_length;
	int		    endian;
    int         x;
    int         y;
    int         range;
    int         init_y;
}				t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void close()
{
    
}

int	key_hook(int keycode, t_vars *vars)
{
    vars->init_y = vars->x;
    vars->range += 50;
	vars->img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
								&vars->endian);
    while (vars->x < vars->range)
    {
        vars->y = vars->init_y;
        while (vars->y < vars->range)
        {
            my_mlx_pixel_put(vars, vars->x, vars->y, 0xff0000);
            vars->y++;
        }
        vars->x++;
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img,0, 0);
    
    return (0);
}

int	main(void)
{
	t_vars	vars;

    vars.x = 0;
    vars.y = 0;
    vars.range = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close,&vars);
	mlx_loop(vars.mlx);
}