/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:40:54 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/21 21:00:14 by hbouchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH 1000
# define HEIGHT 1000

# define NBTHREAD 4

# define NB_TXT 4
# define K_ESC 53
# define K_LEFT 123
# define K_RIGHT 124
# define K_UP 126
# define K_DOWN 125

# define NORD 0
# define SUD 1
# define EST 2
# define OUEST 3
# include <mlx.h>
# include <pthread.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct		s_vect_f
{
	float			x;
	float			y;
}					t_vect_f;

typedef struct		s_vect_i
{
	int				x;
	int				y;
}					t_vect_i;

typedef struct		s_texture
{
	void			*img[NB_TXT];
	int				*buf[NB_TXT];
	int				width[NB_TXT];
	int				height[NB_TXT];
}					t_texture;

typedef struct		s_wall
{
	t_vect_i		ext;
	t_vect_i		txt;
	int				side;
	int				color;
	int				dist_wall;
}					t_wall;

typedef struct		s_direct
{
	t_vect_i		curr;
	t_vect_i		step;
	t_vect_f		ray;
	t_vect_f		delta;
	t_vect_f		next;
	double			x_mapped;
	double			dist;
	double			hit;

}					t_direct;

typedef struct		s_wolf3d
{
	t_vect_f		pos_joueur;
	t_vect_f		dir_joueur;
	t_vect_f		plane;
	t_texture		txt;
	int				*map;
	int				width_map;
	int				height_map;
	void			*window;
	void			*image;
	void			*mlx;
	int				*pixels;
	void			*mini_img;
	int				*m_pixels;

	int				bpp;
	int				size_line;
	int				endian;
}					t_wolf3d;

typedef struct		s_thread
{
	t_wolf3d		*w;
	int				x_th;
}					t_thread;

int					parser(t_wolf3d *w3d, char *file, int len, int j);
int					final(t_wolf3d *w3d);
int					mouse(int x, int y, t_wolf3d *w3d);
int					events(int k, t_wolf3d *w3d);
int					draw(t_wolf3d *w3d);
int					texture(t_wolf3d *w3d);
void				multi_thread(t_wolf3d *w3d);
t_wall				raycasting(t_wolf3d *w3d, int x);

#endif
