/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:39:37 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/21 20:19:16 by hbouchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int				final(t_wolf3d *w3d)
{
	int i;

	i = -1;
	while (++i < NB_TXT)
		mlx_destroy_image(w3d->mlx, w3d->txt.img[i]);
	if (w3d->map)
		free(w3d->map);
	mlx_destroy_image(w3d->mlx, w3d->mini_img);
	mlx_destroy_image(w3d->mlx, w3d->image);
	mlx_destroy_window(w3d->mlx, w3d->window);
	exit(0);
	return (0);
}

static void		initializing(t_wolf3d *w3d, char *file)
{
	w3d->height_map = 0;
	w3d->mlx = mlx_init();
	w3d->pos_joueur = (t_vect_f){-1.0, -1.0};
	if (parser(w3d, file, 0, 0) == -1 && write(1, "error: parser fails\n", 20))
		exit(0);
	if (w3d->pos_joueur.x == -1.0 && write(1, "error: need a free space\n", 25))
	{
		free(w3d->map);
		exit(0);
	}
	if (texture(w3d) == -1 && write(1, "error: textures fails\n", 22))
		exit(0);
	w3d->dir_joueur = (t_vect_f){0.0, 1.0};
	w3d->plane = (t_vect_f){-0.66, 0.0};
	w3d->window = mlx_new_window(w3d->mlx, WIDTH, HEIGHT, "WOLF3D");
	w3d->image = mlx_new_image(w3d->mlx, WIDTH, HEIGHT);
	w3d->pixels = (int *)mlx_get_data_addr(w3d->image, &w3d->bpp,
			&w3d->size_line, &w3d->endian);
	w3d->mini_img = mlx_new_image(w3d->mlx, w3d->width_map * 4,
			w3d->height_map * 4);
	w3d->m_pixels = (int *)mlx_get_data_addr(w3d->mini_img, &w3d->bpp,
			&w3d->size_line, &w3d->endian);
}

int				main(int argc, char **argv)
{
	t_wolf3d w3d;

	if (argc != 2 && write(1, "usage: ./wolf3d file\n", 21))
		return (0);
	initializing(&w3d, argv[1]);
	draw(&w3d);
	mlx_hook(w3d.window, 17, 0, final, &w3d);
	mlx_hook(w3d.window, 2, 0, events, &w3d);
	mlx_hook(w3d.window, 6, 0, mouse, &w3d);
	mlx_loop(w3d.mlx);
	return (0);
}
