/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:41:37 by malbayra          #+#    #+#             */
/*   Updated: 2024/10/28 13:53:57 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_split(char **_tab)
{
	int	i;

	i = 0;
	if (_tab)
	{
		while (_tab[i])
		{
			free(_tab[i]);
			i++;
		}
		free(_tab);
	}
}

static int	ft_countwords(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_fill_tab(char const *s, char c, char **tab)
{
	int		i;
	int		k;
	int		tab_index;

	i = 0;
	tab_index = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[i] != c && s[i])
			i++;
		if (i > k)
		{
			tab[tab_index] = ft_substr(s, k, i - k);
			if (!tab[tab_index])
				return (ft_free_split(tab), NULL);
			tab_index++;
		}
	}
	tab[tab_index] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!tab)
		return (NULL);
	return (ft_fill_tab(s, c, tab));
}
