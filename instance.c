int instance(t_data *vars)
{	
	size_t	i;
	int color_shift;
	color_shift = 0;
	// mlx_destroy_image(vars->mlx, vars->img2);
	// vars->img2 = mlx_new_image(vars->mlx, 1920, 1080);
	// vars->addr2 = mlx_get_data_addr(vars->img2, &vars->bits_per_pixel, &vars->line_length,
	// 									&vars->endian);
	mandelbrot_set(vars, 0,color_shift);
	// color_shift++;
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img2, 0, 0);
	// while (i < 1844674407)
	// {	
	// 	while (color_shift < 244)
	// 	{
	// 		// vars->img = mlx_new_image(vars->mlx, 1920, 1080);
	// 		// vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
	// 										// &vars->endian);
	// 		mandelbrot_set(vars, 1, color_shift);
	// 		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
	// 		// mlx_destroy_image(vars->mlx, vars->img2);

	// 		// vars->img2 = mlx_new_image(vars->mlx, 1920, 1080);
	// 		// vars->addr2 = mlx_get_data_addr(vars->img2, &vars->bits_per_pixel, &vars->line_length,
	// 		// /							&vars->endian);
	// 		mandelbrot_set(vars, 0,color_shift);
	// 		// mlx_destroy_image(vars->mlx, vars->img);
	// 		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img2, 0, 0);
	// 		color_shift++;
	// 	}
	// 	while (color_shift > 1)
	// 	{
	// 		// vars->img = mlx_new_image(vars->mlx, 1920, 1080);
	// 		// vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length,
	// 		// 							&vars->endian);
	// 		mandelbrot_set(vars, 1, color_shift);
	// 		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
	// 		// mlx_destroy_image(vars->mlx, vars->img2);

	// 		// vars->img2 = mlx_new_image(vars->mlx, 1920, 1080);
	// 		// vars->addr2 = mlx_get_data_addr(vars->img2, &vars->bits_per_pixel, &vars->line_length,
	// 		// 						&vars->endian);
	// 		mandelbrot_set(vars, 0,color_shift);
	// 		// mlx_destroy_image(vars->mlx, vars->img);
	// 		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img2, 0, 0);
	// 		color_shift--;
	// 	}
	// 	i++;
	// }
	mlx_hook(vars->mlx_win, 2, 1L<<0, close, vars);
	mlx_hook(vars->mlx_win, 17, 1L<<5, close2, vars);
	// mlx_hook(vars->mlx_win, 22, 1L<<18, resize, vars);
	return(0);
}