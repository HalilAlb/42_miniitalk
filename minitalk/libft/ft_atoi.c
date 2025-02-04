/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:39:28 by malbayra          #+#    #+#             */
/*   Updated: 2024/10/14 11:44:20 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	tmp;

	i = 0;
	a = 1;
	tmp = 0;
	while (str[i] == ' ' || (str[i] <= '\r' && str[i] >= '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = tmp * 10 + str[i] - 48;
		i++;
	}
	return (tmp * a);
}
