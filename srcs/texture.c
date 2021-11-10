/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:39:21 by hbouchak          #+#    #+#             */
/*   Updated: 2020/01/21 20:59:08 by hbouchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int			texture(t_wolf3d *w3d)
{
	char	*filename;
	int		i;

	i = -1;
	while (++i < NB_TXT)
	{
		filename = ft_strjoin2("xpm/", ft_strjoin2(ft_itoa(i), ".xpm", 0), 1);
		w3d->txt.img[i] = mlx_xpm_file_to_image(w3d->mlx,
				filename, &w3d->txt.width[i],
					&w3d->txt.height[i]);
		free(filename);
	}
	while (--i >= 0)
		if (!w3d->txt.img[i])
			return (-1);
	i = -1;
	while (++i < NB_TXT)
		w3d->txt.buf[i] = (int *)mlx_get_data_addr(w3d->txt.img[i], &w3d->bpp,
				&w3d->size_line, &w3d->endian);
	return (1);
}
