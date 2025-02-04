/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:25:00 by malbayra          #+#    #+#             */
/*   Updated: 2024/10/17 12:12:52 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	make_job(long nb, int *level, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb > 9)
	{
		make_job(nb / 10, level, fd);
		make_job(nb % 10, level, fd);
	}
	else
	{
		ft_putchar_fd(nb + '0', fd);
		(*level)++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		level;
	long	nb;

	level = 0;
	nb = n;
	make_job(nb, &level, fd);
}
