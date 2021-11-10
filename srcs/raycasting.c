/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:39:18 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/21 20:27:00 by hbouchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	init_raycasting(t_direct *h, t_wolf3d *w3d, int x)
{
	h->x_mapped = 2 * x / (double)WIDTH - 1;
	h->ray.x = w3d->dir_joueur.x + w3d->plane.x * h->x_mapped;
	h->ray.y = w3d->dir_joueur.y + w3d->plane.y * h->x_mapped;
	h->curr.x = floor(w3d->pos_joueur.x);
	h->curr.y = floor(w3d->pos_joueur.y);
	h->delta.x = fabs(1.0 / h->ray.x);
	h->delta.y = fabs(1.0 / h->ray.y);
	h->step.x = h->ray.x < 0 ? -1 : 1;
	h->next.x = h->ray.x < 0 ? (w3d->pos_joueur.x - h->curr.x) * h->delta.x :
		(h->curr.x + 1.0 - w3d->pos_joueur.x) * h->delta.x;
	h->step.y = h->ray.y < 0 ? -1 : 1;
	h->next.y = h->ray.y < 0 ? (w3d->pos_joueur.y - h->curr.y) * h->delta.y :
		(h->curr.y + 1.0 - w3d->pos_joueur.y) * h->delta.y;
}

void	find_wall(t_direct *h, t_wall *r, t_wolf3d *w3d)
{
	while (h->curr.x >= 0 && h->curr.x < w3d->width_map
			&& h->curr.y >= 0 && h->curr.y < w3d->height_map)
	{
		if (h->next.x < h->next.y)
		{
			h->next.x += h->delta.x;
			h->curr.x += h->step.x;
			r->side = (int)w3d->pos_joueur.x < h->curr.x ? EST : OUEST;
		}
		else
		{
			h->next.y += h->delta.y;
			h->curr.y += h->step.y;
			r->side = (int)w3d->pos_joueur.y > h->curr.y ? NORD : SUD;
		}
		if (w3d->map[h->curr.x + w3d->width_map * h->curr.y] != 0)
			break ;
	}
	if (r->side == OUEST || r->side == EST)
		h->dist = (h->curr.x - w3d->pos_joueur.x
				+ (1 - h->step.x) / 2) / h->ray.x;
	else
		h->dist = (h->curr.y - w3d->pos_joueur.y +
				(1 - h->step.y) / 2) / h->ray.y;
}

t_wall	raycasting(t_wolf3d *w3d, int x)
{
	t_wall		r;
	t_direct	h;

	init_raycasting(&h, w3d, x);
	find_wall(&h, &r, w3d);
	r.dist_wall = (int)(HEIGHT / h.dist);
	r.ext.x = -r.dist_wall / 2 + HEIGHT / 2;
	r.ext.x = (r.ext.x < 0) ? 0 : r.ext.x;
	r.ext.y = r.dist_wall / 2 + HEIGHT / 2;
	r.ext.y = (r.ext.y >= HEIGHT) ? HEIGHT - 1 : r.ext.y;
	if (r.side == OUEST || r.side == EST)
		h.hit = w3d->pos_joueur.y + h.dist * h.ray.y;
	else
		h.hit = w3d->pos_joueur.x + h.dist * h.ray.x;
	h.hit -= floor(h.hit);
	r.txt.x = (int)(h.hit * (double)(w3d->txt.width[r.side]));
	return (r);
}
