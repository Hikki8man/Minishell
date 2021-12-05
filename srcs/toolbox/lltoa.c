/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:09 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:10 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	get_nb_len(long long nb)
{
	int					len;
	unsigned long long	n;

	len = 0;
	if (nb == 0)
		return (1);
	n = (unsigned long long)nb;
	if (nb < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*lltoa(long long nb)
{
	char				*str;
	int					len;
	int					start;
	unsigned long long	n;

	start = 0;
	len = get_nb_len(nb);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	n = (unsigned long long)nb;
	if (nb < 0)
	{
		*str = '-';
		start = 1;
	}
	while (--len >= start)
	{
		str[len] = (char)(n % 10 + 48);
		n /= 10;
	}
	return (str);
}
