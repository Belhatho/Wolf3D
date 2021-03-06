/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 01:50:08 by belhatho          #+#    #+#             */
/*   Updated: 2019/05/20 01:50:23 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t			size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

size_t	ft_strlen2(char **twodim)
{
	int		s;

	s = 0;
	while (twodim[s])
		s++;
	return (s);
}
