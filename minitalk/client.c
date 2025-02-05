/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:03:25 by malbayra          #+#    #+#             */
/*   Updated: 2025/02/05 14:49:11 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_str(int pid, char *str)
{
	static int	bit_index = 0;
	static char	*message = 0;
	char		current_char;
	int			current_bit;

	if (str)
		message = str;
	if (message && message[bit_index / 8])
	{
		current_char = message[bit_index / 8];
		current_bit = (current_char >> (bit_index % 8)) & 1;
		if (current_bit == 1 && kill(pid, SIGUSR2) == -1)
			ft_printf("%s", "Error KILL\n");
		else if (current_bit == 0 && kill(pid, SIGUSR1) == -1)
			ft_printf("%s", "Error KILL\n");
		bit_index++;
	}
	else if (message)
	{
		while (bit_index++ < 8)
			if (kill(pid, SIGUSR1) == -1)
				ft_printf("%s", "Error KILL\n");
		exit(0);
	}
}

void	ft_receipt(int sig, siginfo_t *info, void *context)
{
	static int	pid = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (sig == SIGUSR1)
		ft_send_str(pid, NULL);
	else if (sig == SIGUSR2)
		exit(0);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;

	if (ac != 3 || ft_strlen(av[1]) > 8
		|| ft_strncmp(av[1], "0123456789", 10) == 0)
	{
		ft_printf("ERROR: Invalid Argument Or PID\n");
		ft_printf("USED: ./client <server_pid> <string>\n");
		return (1);
	}
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0 || server_pid >= 4194304)
		return (ft_printf("Error: Invalid PID\n"), 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receipt;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_printf("Error: sigaction\n"), 1);
	ft_send_str(server_pid, av[2]);
	while (1)
		pause();
}
