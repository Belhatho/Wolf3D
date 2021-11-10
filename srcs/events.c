/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:39:09 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/22 14:26:21 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

static void		rotation(t_vect_f *dir, t_vect_f *plane, double angle)
{
	double		oldx;

	oldx = dir->x;
	dir->x = dir->x * cos(angle) - dir->y * sin(angle);
	dir->y = oldx * sin(angle) + dir->y * cos(angle);
	oldx = plane->x;
	plane->x = plane->x * cos(angle) - plane->y * sin(angle);
	plane->y = oldx * sin(angle) + plane->y * cos(angle);
}

static void		move(t_wolf3d *w3d, t_vect_f next)
{
	if (w3d->map[(int)next.x + (int)w3d->pos_joueur.y * w3d->width_map] == 0
		&& next.x >= 0.0001 && (int)next.x < w3d->width_map)
		w3d->pos_joueur.x = next.x;
	if (w3d->map[(int)w3d->pos_joueur.x + w3d->width_map * (int)next.y] == 0
		&& next.x >= 0.0001 && (int)next.y < w3d->height_map)
		w3d->pos_joueur.y = next.y;
}

int				events(int key, t_wolf3d *w3d)
{
	t_vect_f		next;

	if (key == K_ESC)
		final(w3d);
	if (key == K_UP)
	{
		next.x = w3d->pos_joueur.x + w3d->dir_joueur.x * 0.05;
		next.y = w3d->pos_joueur.y + w3d->dir_joueur.y * 0.05;
		move(w3d, next);
	}
	if (key == K_DOWN)
	{
		next.x = w3d->pos_joueur.x - w3d->dir_joueur.x * 0.05;
		next.y = w3d->pos_joueur.y - w3d->dir_joueur.y * 0.05;
		move(w3d, next);
	}
	if (key == K_RIGHT)
		rotation(&w3d->dir_joueur, &w3d->plane, 5.0 * M_PI / 180.0);
	if (key == K_LEFT)
		rotation(&w3d->dir_joueur, &w3d->plane, -5.0 * M_PI / 180.0);
	(key == K_UP || key == K_DOWN || key == K_RIGHT
	|| key == K_LEFT) ? draw(w3d) : 0;
	return (1);
}

int				mouse(int x, int y, t_wolf3d *w3d)
{
	static int	old_x = 0;

	(void)y;
	if (x < old_x - 5 || x > old_x + 5)
	{
		if (x > old_x)
			rotation(&w3d->dir_joueur, &w3d->plane, 5.0 * M_PI / 180.0);
		else
			rotation(&w3d->dir_joueur, &w3d->plane, -5.0 * M_PI / 180.0);
		old_x = x;
		draw(w3d);
	}
	return (1);
}
