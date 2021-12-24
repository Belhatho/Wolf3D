/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 00:54:28 by belhatho          #+#    #+#             */
/*   Updated: 2021/11/12 00:54:30 by belhatho         ###   ########.fr       */
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


int			borders(t_wolf3d *w3d)
{
    int i = -1;

    while (++i < w3d->width_map)
        if (w3d->map[i] == 0)
            return (-1);
    while (i < w3d->width_map * (w3d->height_map - 1))
    {
        if (w3d->map[i] == 0 || w3d->map[i + w3d->width_map - 1] == 0)
            return (-1);
        i = i + w3d->width_map;
    }
    while (i < w3d->width_map * w3d->height_map)
        if (w3d->map[i++] == 0)
            return (-1);
    return (1);
}

void     print(t_wolf3d *w3d)
{
    int i = 0;
    
    while (i < (w3d->width_map * w3d->height_map))
    {
        ft_putnbr(w3d->map[i]);
        ft_putstr("#");
        if ((i != 0) && (i + 1) % w3d->width_map == 0)
        {
            ft_putstr("$\n");
        }
        i++;
    }
	return (0);
}

static void		initializing(t_wolf3d *w3d, char *file)
{
	w3d->height_map = 0;
	w3d->mlx = mlx_init();
	w3d->pos_joueur = (t_vect_f){-1.0, -1.0};
	if (parser(w3d, file, 0) == -1 && write(1, "error: parser fails\n", 20))
		exit(0);
	
	print(w3d);

	if ((w3d->pos_joueur.x == -1.0 || borders(w3d) == -1) &&
	write(1, "error: no free space OR no closed borders\n", 42))
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
