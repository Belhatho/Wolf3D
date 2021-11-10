/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:39:47 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/21 20:56:48 by hbouchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

static int	free_all(char ***split, char **line, int **map, int fd)
{
	int		i;
	char	**f_split;

	i = 0;
	f_split = *split;
	while (f_split[i])
	{
		free(f_split[i]);
		f_split[i] = NULL;
		i++;
	}
	if (*line)
		free(*line);
	*line = NULL;
	if (*map)
		free(*map);
	*map = NULL;
	close(fd);
	return (-1);
}

static void	set_square(t_wolf3d *w3d, char **split, int j)
{
	int square;

	square = ft_atoi(split[j]);
	if (square == 0 && w3d->pos_joueur.x == -1.0)
	{
		w3d->pos_joueur.x = j + 0.2;
		w3d->pos_joueur.y = w3d->height_map + 0.2;
	}
	w3d->map[w3d->height_map * w3d->width_map + j] = square;
}

static void	aux(t_wolf3d *w3d, int len, char **split, char *line)
{
	int j;

	j = -1;
	while (++j < len)
		set_square(w3d, split, j);
	ft_free(&split);
	free(line);
}

int			parser(t_wolf3d *w3d, char *file, int len, int j)
{
	char	**split;
	char	*line;
	int		fd;

	line = NULL;
	w3d->map = NULL;
	if ((fd = open(file, O_RDONLY)) == -1 || read(fd, line, 0) < 0)
		return (-1);
	while (get_next_line(fd, &line) > 0 && (j = -1))
	{
		split = ft_strsplit(line, ' ');
		len = ft_strlen2(split);
		w3d->width_map = w3d->height_map == 0 ? len : w3d->width_map;
		if (w3d->width_map != len)
			return (free_all(&split, &line, &w3d->map, fd));
		if (!(w3d->map = (int*)ft_realloc((void*)(&w3d->map), sizeof(int)
						* w3d->height_map
							* w3d->width_map, sizeof(int)
								* (w3d->height_map + 1) * w3d->width_map)))
			return (free_all(&split, &line, &w3d->map, fd));
		aux(w3d, len, split, line);
		w3d->height_map++;
	}
	return (close(fd));
}
