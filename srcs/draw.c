/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:38:51 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/21 20:15:19 by hbouchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

static void		*process(t_thread *p)
{
	t_wall		r;
	int			x;
	int			y;

	x = (p->x_th * WIDTH / NBTHREAD) - 1;
	while (++x < (p->x_th + 1) * WIDTH / NBTHREAD)
	{
		r = raycasting(p->w, x);
		y = r.ext.x - 1;
		while (++y < r.ext.y && y < HEIGHT)
		{
			r.txt.y = y + (r.dist_wall / 2) - (HEIGHT / 2);
			r.txt.y = p->w->txt.height[r.side] * r.txt.y / r.dist_wall;
			r.color = p->w->txt.buf[r.side][p->w->txt.width[r.side]
				* r.txt.y + r.txt.x];
			p->w->pixels[x + WIDTH * y] = r.color;
		}
		if (r.ext.x > 0 && (y = -1) < 0)
			while (++y < r.ext.x)
				p->w->pixels[x + WIDTH * y] = 0x0000ff;
		if (r.ext.y < HEIGHT && (y = r.ext.y - 1) < HEIGHT)
			while (++y < HEIGHT)
				p->w->pixels[x + WIDTH * y] = 0x7F493E;
	}
	pthread_exit(NULL);
}

void			multi_thread(t_wolf3d *w3d)
{
	t_thread	t[NBTHREAD];
	pthread_t	p[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		t[i].x_th = i;
		t[i].w = w3d;
		pthread_create(&p[i], NULL, (void*)process, &t[i]);
	}
	while (--i >= 0)
		pthread_join(p[i], NULL);
}

static void		small_map(t_wolf3d *w3d)
{
	int		x;
	int		y;

	x = -1;
	while (++x < w3d->width_map * 4 && (y = -1))
		while (++y < w3d->height_map * 4)
		{
			w3d->m_pixels[y * w3d->width_map * 4 + x] = 0xAA000000;
			if (w3d->map[(y / 4) * w3d->width_map + (x / 4)] == 0)
				w3d->m_pixels[y * w3d->width_map * 4 + x] = 0xAAFFFFFF;
			if (x / 4 == (int)w3d->pos_joueur.x && \
				y / 4 == (int)w3d->pos_joueur.y)
				w3d->m_pixels[y * w3d->width_map * 4 + x] = 0xAAFF0000;
		}
}

int				draw(t_wolf3d *w3d)
{
	bzero(w3d->pixels, WIDTH * HEIGHT * 4);
	multi_thread(w3d);
	mlx_put_image_to_window(w3d->mlx, w3d->window, w3d->image, 0, 0);
	small_map(w3d);
	mlx_put_image_to_window(w3d->mlx, w3d->window, w3d->mini_img, 0, 0);
	return (1);
}
